#include "Texture.h"

Texture::Texture()
{
}
Texture::~Texture()
{
}

bool Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string& materialLib)
{


	return true;
}

bool Texture::LoadMTL(ID3D11Device* device, ID3D11DeviceContext* deviceContext, std::string& materialLib)
{
	std::ifstream file;
	std::string line;
	std::string junk;
	std::stringstream ss;
	int nrOfMaterials = 0;
	bool firstTextureLoad = true;
	int height;
	int width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hresult;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	std::string path = "../Ze3DProject/Textures/";
	std::string finalPath;
	std::string mtlPath = "../Ze3DProject/OBJ/";
	std::string finalMtlPath = mtlPath + materialLib;
	bool result;

	file.open(finalMtlPath);
	if (!file.is_open()) {
		return false;
	}

	while (std::getline(file, line)) {
		if (line.size() > 0) {
			if (line.substr(0, 6) == "newmtl") { //Create a new material
				ss.clear();
				ss.str(line);
				Material tempMat;
				this->materials.push_back(tempMat);
				ss >> junk >> this->materials.at(nrOfMaterials).name;
				this->materials.at(nrOfMaterials).hasTexture = false;
				this->materials.at(nrOfMaterials).textureIndex = 0;
				this->materials.at(nrOfMaterials).hasNormMap = false;
				this->materials.at(nrOfMaterials).normMapIndex = 0;
				this->materials.at(nrOfMaterials).diffColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				this->materials.at(nrOfMaterials).ambientColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				this->materials.at(nrOfMaterials).specColor = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
				nrOfMaterials++;
			}
			else if (line.at(0) == 'K') {
				ss.clear();
				ss.str(line);
				if (line.at(1) == 'd') { //Save the diffuse color
					ss >> junk >> this->materials.at(nrOfMaterials - 1).diffColor.x
						>> this->materials.at(nrOfMaterials - 1).diffColor.y
						>> this->materials.at(nrOfMaterials - 1).diffColor.z;
				}
				else if (line.at(1) == 'a') { //If there has been no diffuse, save ambient as diffuse
					ss >> junk >> this->materials.at(nrOfMaterials - 1).ambientColor.x
						>> this->materials.at(nrOfMaterials - 1).ambientColor.y
						>> this->materials.at(nrOfMaterials - 1).ambientColor.z;
				}
				else if (line.at(1) == 's') { //Save the specular color
					ss >> junk >> this->materials.at(nrOfMaterials - 1).specColor.x
						>> this->materials.at(nrOfMaterials - 1).specColor.y
						>> this->materials.at(nrOfMaterials - 1).specColor.z;
				}
			}
			else if (line.at(0) == 'N') { //Save the transparency
				if (line.at(1) == 's') {
					float specPwr = 0.0f;
					ss.clear();
					ss.str(line);
					ss >> junk >> specPwr;

					this->materials.at(nrOfMaterials - 1).specPower = specPwr;
				}
			}
			else if (line.substr(0, 6) == "map_Kd") { //Path to texture file
				if (line.size() > 8) {
					bool beenLoaded = false;
					std::string textureFilename;
					ss.clear();
					ss.str(line);
					ss >> junk >> textureFilename;

					for (int i = 0; !beenLoaded && i < this->textureNames.size(); i++) { //Check if it's been loaded for this model beofre
						if (this->textureNames.at(i) == textureFilename) {
							this->materials.at(nrOfMaterials - 1).hasTexture = true;
							this->materials.at(nrOfMaterials - 1).textureIndex = i;
							beenLoaded = true;
						}
					}
					if (!beenLoaded) {
						//Load the targa image data into memory
						finalPath = path + textureFilename;
						result = this->LoadTarga(finalPath.c_str(), height, width);
						if (!result) {
							return false;
						}

						//If it's the first texture, init some general desc values
						if (firstTextureLoad) {
							//Setup the description of the texture
							textureDesc.MipLevels = 0;
							textureDesc.ArraySize = 1;
							textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
							textureDesc.SampleDesc.Count = 1;
							textureDesc.SampleDesc.Quality = 0;
							textureDesc.Usage = D3D11_USAGE_DEFAULT;
							textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
							textureDesc.CPUAccessFlags = 0;
							textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

							//Setup the shader resource view description
							srvDesc.Format = textureDesc.Format;
							srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
							srvDesc.Texture2D.MostDetailedMip = 0;
							srvDesc.Texture2D.MipLevels = -1;
						}
						//Set the teexture specific description values
						textureDesc.Height = height;
						textureDesc.Width = width;

						//Create the empty texture
						hresult = device->CreateTexture2D(&textureDesc, NULL, &this->texture);
						if (FAILED(hresult)) {
							return false;
						}

						//Set the row pitch of the targa data
						rowPitch = (width * 4) * sizeof(unsigned char);

						//Copy the targa image data into the texture
						deviceContext->UpdateSubresource(this->texture, 0, NULL, this->targaData, rowPitch, 0);

						//Create the shader resource view for the texture
						ID3D11ShaderResourceView* tempTextureView;

						hresult = device->CreateShaderResourceView(this->texture, &srvDesc, &tempTextureView);
						if (FAILED(hresult)) {
							return false;
						}
						this->textureNames.push_back(textureFilename);
						this->materials.at(nrOfMaterials - 1).hasTexture = true;
						this->materials.at(nrOfMaterials - 1).textureIndex = this->textureViews.size();
						this->textureViews.push_back(tempTextureView);

						//Release the texture
						if (this->texture) {
							this->texture->Release();
							this->texture = nullptr;
						}
						//Release the targa image data now that the image data has been loaded into the texture
						delete[] this->targaData;
						this->targaData = nullptr;
					}
				}

			}
			else if (line.substr(0, 8) == "map_bump") { //Path to normal map
				if (line.size() > 8) {
					bool beenLoaded = false;
					std::string textureFilename;
					ss.clear();
					ss.str(line);
					ss >> junk >> textureFilename;

					for (int i = 0; !beenLoaded && i < this->textureNames.size(); i++) { //If the normal map has been loaded before, use that
						if (this->textureNames.at(i) == textureFilename) {
							this->materials.at(nrOfMaterials - 1).hasTexture = true;
							this->materials.at(nrOfMaterials - 1).textureIndex = i;
							beenLoaded = true;
						}
					}
					if (!beenLoaded) {
						//Load the targa image data into memory
						finalPath = path + textureFilename;
						result = this->LoadTarga(finalPath.c_str(), height, width);
						if (!result) {
							return false;
						}

						//If it's the first texture, init some general desc values
						if (firstTextureLoad) {
							//Setup the description of the texture
							textureDesc.MipLevels = 0;
							textureDesc.ArraySize = 1;
							textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
							textureDesc.SampleDesc.Count = 1;
							textureDesc.SampleDesc.Quality = 0;
							textureDesc.Usage = D3D11_USAGE_DEFAULT;
							textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
							textureDesc.CPUAccessFlags = 0;
							textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

							//Setup the shader resource view description
							srvDesc.Format = textureDesc.Format;
							srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
							srvDesc.Texture2D.MostDetailedMip = 0;
							srvDesc.Texture2D.MipLevels = -1;
						}
						//Set the teexture specific description values
						textureDesc.Height = height;
						textureDesc.Width = width;

						//Create the empty texture
						hresult = device->CreateTexture2D(&textureDesc, NULL, &this->texture);
						if (FAILED(hresult)) {
							return false;
						}

						//Set the row pitch of the targa data
						rowPitch = (width * 4) * sizeof(unsigned char);

						//Copy the targa image data into the texture
						deviceContext->UpdateSubresource(this->texture, 0, NULL, this->targaData, rowPitch, 0);

						//Create the shader resource view for the texture
						ID3D11ShaderResourceView* tempTextureView;

						hresult = device->CreateShaderResourceView(this->texture, &srvDesc, &tempTextureView);
						if (FAILED(hresult)) {
							return false;
						}
						this->textureNames.push_back(textureFilename);
						this->materials.at(nrOfMaterials - 1).hasNormMap = true;
						this->materials.at(nrOfMaterials - 1).normMapIndex = this->textureViews.size();
						this->textureViews.push_back(tempTextureView);

						//Release the texture
						if (this->texture) {
							this->texture->Release();
							this->texture = nullptr;
						}
						//Release the targa image data now that the image data has been loaded into the texture
						delete[] this->targaData;
						this->targaData = nullptr;
					}
				}

			}
		}
	}
	file.close();

	return true;
}