#pragma once

//===============================================.
//	マクロ(define定義は基本1行).
//===============================================.

//解放.
#define SAFE_RELEASE(p) if(p!=nullptr){(p)->Release();(p)=nullptr;}

//破棄.
#define SAFE_DELETE(p) if(p!=nullptr){delete (p);(p)=nullptr;}
#define SAFE_DELETE_ARRAY(p)	\
{								\
	if (p != nullptr) {			\
		delete[](p);			\
		(p) = nullptr;			\
	}							\
}