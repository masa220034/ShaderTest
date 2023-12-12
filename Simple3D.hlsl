//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D	g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global:register(b0)
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4    matW;           // ワールド行列
	float4x4	matNormal;	    //ワールド行列
	float4		diffuseColor;	// マテリアルの色＝拡散反射係数
	bool		isTextured;		// テクスチャ貼ってあるかどうか
};

cbuffer global:register(b1)
{
	float4      lightPosition;  //点光源座標
	float4      eyePosition;    //視点座標
	float4      specular;
	float       shuniness;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION; //位置
	float2 uv	  : TEXCOORD;	 //UV座標
	float4 color  : COLOR;	     //色（明るさ）
	float4 eyev   : POSITION;    //ワールド座標系の座標
	float4 normal : NORMAL;      //ワールド座標系の法線
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;
	normal.w = 0;
	normal = mul(normal , matNormal);
	normal = normalize(normal);
	outData.normal = normal;

	float4 light = normalize(lightPosition); //光源ベクトル
	//light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 1.0);   //ライト色＆明るさ Iin
	float4 ambientSource = float4(0.2, 0.2, 0.2, 1.0); //アンビエント係数 Ka
	float4 diffuse;
	float4 ambient;
	float4 NL = dot(inData.normal, normalize(lightPosition)); //面の明るさ
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition)); //反射ベクトルを求めてる
	float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), 8);

	if (isTextured == 0)
	{
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambientSource;
	}
	else
	{
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientSource;
	}

	return diffuse + ambient + specular;
}