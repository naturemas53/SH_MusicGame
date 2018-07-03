#include "SPINE.h"
#include "../../../ESGLib.h"

void Listener(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event){

	ISpine* esSpine = (ISpine*)state->userData;

	if(!esSpine) return;

	switch (type) {
   // 
   case SP_ANIMATION_START:
	  esSpine->NoticeAnimationStart();
      break;
   case SP_ANIMATION_END:
   case SP_ANIMATION_COMPLETE:
	   esSpine->NoticeAnimationEnd();
      break;
   default:
	   break;
   }

}

CSpine::CSpine(spSkeletonData* skeletonData, spAnimationStateData* animationStateData){

	this->skeleton_ = spSkeleton_create(skeletonData);
	this->animasionstate_ = spAnimationState_create(animationStateData);
	this->animasionstate_->listener = Listener;
	this->animasionstate_->userData = this;

	this->bone = nullptr;

}

CSpine::~CSpine(){

	spSkeleton_dispose(this->skeleton_);
	spAnimationState_dispose(this->animasionstate_);

}

void CSpine::Update(){

	float deltatime = (float)GameTimer.GetElapsedMilliSecond() / 1000.0f;

	spAnimationState_apply(this->animasionstate_, this->skeleton_);
	spAnimationState_update(this->animasionstate_,deltatime);
	spSkeleton_updateWorldTransform(this->skeleton_);

}

void CSpine::Draw(){

	spSlot* slot;
	for (int i = 0; i < this->skeleton_->slotsCount;i++){

		slot = this->skeleton_->drawOrder[i];

		spAttachment* attachment = slot->attachment;
		if (!attachment) continue;

		// Fetch the blend mode from the slot and
		// translate it to the engine blend mode
		int blendmode = 0;
		switch (slot->data->blendMode) {
		case SP_BLEND_MODE_NORMAL:		//alpha blend : src.rgb * (src.a) + dest.rgb * (1.0-src.a)
			GraphicsDevice.SetBlendMode(DXGBLEND_NORMAL);
			break;
		case SP_BLEND_MODE_ADDITIVE:	//add : src.rgb * src.a + dest.rgb
			GraphicsDevice.SetBlendMode(DXGBLEND_ADD);
			break;
		case SP_BLEND_MODE_MULTIPLY:	//multiply/modulate : (src.rgb * src.a) * dest.rgb

			break;
		case SP_BLEND_MODE_SCREEN:		//screen : (src.rgb * src.a + dest.rgb) - (src.rgb * src.a * dest.rgb) == ((src.rgb * src.a) * inv(dest.rgb)) + (1.0 * dest.rgb)
			
			break;
		}

		// Calculate the tinting color based on the skeleton's color
		// and the slot's color. Each color channel is given in the
		// range [0-1], you may have to multiply by 255 and cast to
		// and int if your engine uses integer ranges for color channels.
		spColor mulcol, screencol;
		mulcol.r = this->skeleton_->color.r * slot->color.r;
		mulcol.g = this->skeleton_->color.g * slot->color.g;
		mulcol.b = this->skeleton_->color.b * slot->color.b;
		mulcol.a = this->skeleton_->color.a * slot->color.a;
		screencol.r = 0.0f;
		screencol.g = 0.0f;
		screencol.b = 0.0f;
		screencol.a = 0.0f;
		if (slot->darkColor != nullptr) {
			screencol.r = slot->darkColor->r;
			screencol.g = slot->darkColor->g;
			screencol.b = slot->darkColor->b;
			screencol.a = slot->darkColor->a;
		}

		// Fill the vertices array depending on the type of attachment
		if (attachment->type == SP_ATTACHMENT_REGION) {
			//myCustomDraw_region(slot, attachment, &mulcol, blendmode);
			this->RegionDraw(slot,attachment,&mulcol,0);
		}
		else if (attachment->type == SP_ATTACHMENT_MESH) {
			this->MeshDraw(slot,attachment,&mulcol,0);
		}
		else {
			//unsupport
		}

	}

}

void CSpine::RegionDraw(spSlot* slot, spAttachment* attachment, spColor* col, int blendmode){

	// Cast to an spRegionAttachment so we can get the rendererObject
	// and compute the world vertices
	spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;

	// Check the number of vertices in the mesh attachment.
	std::vector<float> worldvertex = std::vector<float>(4 * 2);

	// Our engine specific Texture is stored in the spAtlasRegion which was
	// assigned to the attachment on load. It represents the texture atlas
	// page that contains the image the region attachment is mapped to
	SPRITE textureptr = nullptr;
	textureptr = (SPRITE)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;

	// Computed the world vertices positions for the 4 vertices that make up
	// the rectangular region attachment. This assumes the world transform of the
	// bone to which the slot (and hence attachment) is attached has been calculated
	// before rendering via spSkeleton_updateWorldTransform
	spRegionAttachment_computeWorldVertices(regionAttachment, slot->bone, worldvertex.data(), 0, 2);

	// Create 2 triangles, with 3 vertices each from the region's
	// world vertex positions and its UV coordinates (in the range [0-1]).

	// 「Computed the world vertices positions for the 4 vertices that make up」
	// が正確な情報で、4頂点分を計算します。
	// つまり、0,1,2 と 2,3,0 の2個の三角形を形成します。

	const int idxtbl[6] = { 0, 1, 2, 2, 3, 0 };

	DXGTLVERTEX   vertex[6];
	Color color = Color(1.0f,1.0f,1.0f);
	color.R(col->r);
	color.G(col->g);
	color.B(col->b);
	color.A(col->a);
	int triangleindex = 0;
	float* sptr = (float*)worldvertex.data();
	int n = 2;
	for (int i = 0; i < n; i++) {
		//triangle
		for (int j = 0; j < 3; j++) {
			//vertex
			int idx = idxtbl[triangleindex] * 2;
			triangleindex++;

			vertex[i * 3 + j].x = sptr[idx + 0];
			vertex[i * 3 + j].y = sptr[idx + 1];

			vertex[i * 3 + j].tu = regionAttachment->uvs[idx + 0];
			vertex[i * 3 + j].tv = regionAttachment->uvs[idx + 1];

			vertex[i * 3 + j].color = color;

			/*
			xx[j] = sptr[idx + 0];
			yy[j] = sptr[idx + 1];
			uu[j] = regionAttachment->uvs[idx + 0];
			vv[j] = regionAttachment->uvs[idx + 1];
			*/
		}
		


	}

	GraphicsDevice.SetTexture(0, *textureptr);
	GraphicsDevice.DrawUserPrimitives(D3DPT_TRIANGLELIST, vertex, 2, DXGTLVERTEX::FVF());

}

void CSpine::MeshDraw(spSlot* slot, spAttachment* attachment, spColor* col, int blendmode){

	// Cast to an spMeshAttachment so we can get the rendererObject
	// and compute the world vertices
	spMeshAttachment* mesh = (spMeshAttachment*)attachment;

	// Check the number of vertices in the mesh attachment. If it is bigger
	// than our scratch buffer, we don't render the mesh. We do this here
	// for simplicity, in production you want to reallocate the scratch buffer
	// to fit the mesh.
	// if (mesh->super.worldVerticesLength > MAX_VERTICES_PER_ATTACHMENT) continue;
	//worldVerticesLength が　スクリーン向けに頂点を変換する際に必要な数
	std::vector<float> worldvertex = std::vector<float>(mesh->super.worldVerticesLength);

	// Our engine specific Texture is stored in the spAtlasRegion which was
	// assigned to the attachment on load. It represents the texture atlas
	// page that contains the image the mesh attachment is mapped to
	SPRITE textureptr = nullptr;
	textureptr = (SPRITE)((spAtlasRegion*)mesh->rendererObject)->page->rendererObject;	//set user pointer in _spAtlasPage_createTexture

	//親のVertexアタッチメントが必要なんですって
	spVertexAttachment_computeWorldVertices(&mesh->super, slot, 0, mesh->super.worldVerticesLength, worldvertex.data(), 0, 2);	//probably stride value float x,y count 2. support 3D(x,y,z) feature?

	// Mesh attachments use an array of vertices, and an array of indices to define which
	// 3 vertices make up each triangle. We loop through all triangle indices
	// and simply emit a vertex for each triangle's vertex.
	//for (int i = 0; i < mesh->trianglesCount; ++i) {
	//	int index = mesh->triangles[i] << 1;
	//	addVertex(worldVerticesPositions[index], worldVerticesPositions[index + 1],
	//		mesh->uvs[index], mesh->uvs[index + 1],
	//		tintR, tintG, tintB, tintA, &vertexIndex);
	//}

	//描画に必要な分作成すること！
	std::vector<DXGTLVERTEX>  vertexs(mesh->trianglesCount);
	Color color = Color(1.0f, 1.0f, 1.0f);
	color.R(col->r);
	color.G(col->g);
	color.B(col->b);
	color.A(col->a);

	float xx[3], yy[3];	//vertex
	float uu[3], vv[3];	//uv
	int triangleindex = 0;
	float* sptr = worldvertex.data();
	int n = mesh->trianglesCount / 3;
	WORD*  tr = mesh->triangles;
	for (int i = 0; i < n; i++) {
		//triangle
		for (int j = 0; j < 3; j++) {
			//vertex
			int idx = mesh->triangles[triangleindex] * 2;
			triangleindex++;

			vertexs[i * 3 + j].x = sptr[idx + 0];
			vertexs[i * 3 + j].y = sptr[idx + 1];

			vertexs[i * 3 + j].tu = mesh->uvs[idx + 0];
			vertexs[i * 3 + j].tv = mesh->uvs[idx + 1];

			vertexs[i * 3 + j].color = color;

			//xx[j] = sptr[idx + 0];
			//yy[j] = sptr[idx + 1];
			//uu[j] = mesh->uvs[idx + 0];
			//vv[j] = mesh->uvs[idx + 1];
		}

	}

	GraphicsDevice.SetTexture(0, *textureptr);
	GraphicsDevice.DrawUserPrimitives(D3DPT_TRIANGLELIST, vertexs.data(), n, DXGTLVERTEX::FVF());

}

void CSpine::SetAnimation(int playtrack, const char* animename, int isloop, float mixDulation){

	if (!animename){
		spAnimationState_setEmptyAnimation(this->animasionstate_,playtrack,mixDulation);
	}
	else{
		spAnimation* anime = spSkeletonData_findAnimation(this->skeleton_->data, animename);
		if (!anime) return;
		spAnimationState_setAnimation(this->animasionstate_, playtrack, anime, isloop);
	}
}

void CSpine::AddAnimation(int playtrack, const char* animename, float delay, int isloop, float mixDulation){

	if (!animename){
		spAnimationState_addEmptyAnimation(this->animasionstate_, playtrack, mixDulation, delay);
		return;
	}
	else{
		spAnimation* anime = spSkeletonData_findAnimation(this->skeleton_->data, animename);
		if (!anime) return;
		spAnimationState_addAnimation(this->animasionstate_,playtrack,anime,isloop,delay);
	}

}

void CSpine::SetEnptyAnimations(float mixDulation){

	spAnimationState_setEmptyAnimations(this->animasionstate_, mixDulation);

}