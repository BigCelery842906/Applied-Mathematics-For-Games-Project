#pragma once
#include <d3d11.h>
#include "Structures.h"

class Appearance
{
private:
    Geometry _geometry;
    Material _material;
    
    ID3D11ShaderResourceView* _textureRV = nullptr;
public:
    Appearance(Geometry newGeometry, Material newMaterial);
    ~Appearance();
    
    void Draw(ID3D11DeviceContext* pImmediateContext);
    
    Geometry GetGeometryData() const { return _geometry; }
    void SetGeometryData(Geometry newGeometry) { _geometry = newGeometry; }
    // Rendering information
	
    Material GetMaterial() const { return _material; }
    void SetMaterial(Material newMaterial) { _material = newMaterial; }

    void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }
    ID3D11ShaderResourceView* const* GetTextureRV() { return &_textureRV; }
    bool HasTexture() const { return _textureRV ? true : false; }
};
