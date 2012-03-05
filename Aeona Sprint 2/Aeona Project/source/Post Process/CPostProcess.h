#ifndef CPOSTPROCESS_H_
#define CPOSTPROCESS_H_

struct AMBIENT_COLOR
{
	float alpha;
	float red;
	float green;
	float blue;
};

class CPostProcess
{
private:
	CPostProcess(void);
	CPostProcess(const CPostProcess&){}
	CPostProcess& operator=(const CPostProcess&){}
	~CPostProcess(void);

public:
	static CPostProcess* GetInstance(void);

	IDirect3DVertexBuffer9		*quadbuff;
	IDirect3DIndexBuffer9		*quadindex;
	IDirect3DVertexDeclaration9	*cubedecl;
	ID3DXEffect					*postEffect;
	IDirect3DTexture9			*renderTarget;
	IDirect3DSurface9			*current;
	IDirect3DSurface9			*output;

	D3DSURFACE_DESC				backbuffer;

	float						fRed;
	float						fGreen;
	float						fBlue;
	int							colChange;

	AMBIENT_COLOR				ambient;

	const char* techs[7];
	int index;

	void Initialize( void );
	void Update( void );
	void Input( void );
	void BeginPostProcess( void );
	void EndPostProcess( void );
	void ShutDown( void );

	void UpdateColor();
};
#endif