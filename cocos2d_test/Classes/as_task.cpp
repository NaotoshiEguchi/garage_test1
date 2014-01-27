#include "as_task.h"

/*!

*/
AsTaskSystem::AsTaskSystem() :
m_pRoot(NULL),
m_TaskID(0)
{
}

/*!

*/
AsTaskSystem::~AsTaskSystem()
{
	AsTask	*pt, *npt;
	pt = m_pRoot;
	while (pt != NULL) {
		npt = pt->GetNext();
		if (!pt->CheckKill()) {
			pt->Kill();
		}
		delete pt;
		pt = npt;
	}
}

/*!
*/
AsTask *AsTaskSystem::GetRootTask()
{
	return m_pRoot;
}

/*!
*/
void AsTaskSystem::ExecPre()
{
	if (m_pRoot == NULL) {
		return;
	}

	m_pRoot->PreEntry();
}

/*!
*/
void AsTaskSystem::ExecMain()
{
	if (m_pRoot == NULL) {
		return;
	}

	m_pRoot->MainEntry();
}

/*!
*/
void AsTaskSystem::ExecDraw()
{
	if (m_pRoot == NULL) {
		return;
	}

	m_pRoot->DrawEntry(AsTask::STAT_NormalDraw);
}

/*!
*/
void AsTaskSystem::ExecPost()
{
	if (m_pRoot == NULL) {
		return;
	}

	m_pRoot->PostEntry();
}

/*!
*/
void AsTaskSystem::ExecCleanUp()
{
	if (m_pRoot == NULL) {
		return;
	}

	m_pRoot->CleanUpEntry();
}


/*!
	\brief
*/
void AsTaskSystem::ExecCleanUp2()
{
	if (m_pRoot == NULL) {
		return;
	}

	m_pRoot->CleanUpEntry2();
}

/*!
	\brief
	\param
*/
AsTask::AsTask(AsTaskSystem *pSystem) :
m_Status(0),
m_pChild(NULL),
m_pNext(NULL),
m_pParent(NULL),
m_pTaskSystem(pSystem)
{
	s_TaskNumber++;

	SetTag('TASK');

	if (pSystem == NULL) {
		AsAssert(0);
		return;
	}

	m_ID = ++m_pTaskSystem->m_TaskID;

	if (m_pTaskSystem->m_pRoot == NULL) {
		m_pPrev = NULL;
		m_pTaskSystem->m_pRoot = this;
	} else {
		AsTask	*st;
		for (st = m_pTaskSystem->m_pRoot; st->m_pNext != NULL; st = st->m_pNext);
		st->m_pNext = this;
		m_pPrev = st;
	}
	return;
}

/*!
*/
AsTask::AsTask(AsTask *pParent) :
m_Status(0),
m_pChild(NULL),
m_pNext(NULL),
m_pParent(pParent)
{
	s_TaskNumber++;

	SetTag('TASK');

	if (pParent == NULL) {
		AsAssert(0);
		return;
	}

	m_pTaskSystem = pParent->m_pTaskSystem;

	m_ID = ++m_pTaskSystem->m_TaskID;

	if (pParent->m_pChild == NULL) {
		pParent->m_pChild = this;
		m_pPrev = pParent;
	} else {
		AsTask	*st;
		for (st = pParent->m_pChild; st->m_pNext != NULL; st = st->m_pNext)	;
		st->m_pNext = this;
		m_pPrev = st;
	}
}


/*!
*/
AsTask::~AsTask()
{
	s_TaskNumber--;

	//------for CleanUpEntry2----
	if ( m_Status & STAT_Delete ){
		AsAssert( m_pChild == NULL ); 
		return;
	}
	//------for CleanUpEntry2----

	AsTask	*st, *st_next;
	st = m_pChild;
	while (st != NULL) {
		st_next = st->m_pNext;
		if(!st->CheckKill()) {
			st->Kill();
		}
		delete st;
		st = st_next;
	}
	m_pChild = NULL;

	if (m_pPrev != NULL) {
		if(m_pPrev->m_pChild == this) {
			m_pPrev->m_pChild = m_pNext;
		} else {
			m_pPrev->m_pNext = m_pNext;
		}
	} else {
		m_pTaskSystem->m_pRoot = m_pNext;
	}
	if (m_pNext != NULL) {
		m_pNext->m_pPrev = m_pPrev;
	}
}


Sint32 AsTask::s_TaskNumber = 0;
Sint32 AsTask::GetTaskNumber()
{
  return s_TaskNumber;
}

/*!
*/
AsTask *AsTask::_searchSub(Uint32 sid)
{
	AsTask	*st, *ft;
	if (m_ID == sid) {
		return (m_Status & STAT_Dead) ? 0 : this;
	}

	for (st = m_pChild; st != NULL; st = st->m_pNext) {
		ft = st->_searchSub(sid);
		if (ft != NULL)	{
			return ft;
		}
	}
	return NULL;
}

/*!
*/
AsTask *AsTask::Search(Uint32 sid, AsTask *node)
{
	AsTask	*st, *ft;
	if (node == NULL) {
		for (st = m_pTaskSystem->m_pRoot; st != NULL; st = st->m_pNext) {
			ft = st->_searchSub(sid);
			if (ft != NULL) {
				return ft;
			}
		}
	} else {
		return node->_searchSub(sid);
	}
	return NULL;
}

/*!
*/
AsTask *AsTask::_checkExistSub(Uint32 sid)
{
	AsTask	*st, *ft;
	if (m_ID == sid) {
		return this;
	}

	for (st = m_pChild; st != NULL; st = st->m_pNext) {
		ft = st->_checkExistSub(sid);
		if (ft != NULL) {
			return ft;
		}
	}
	return NULL;
}

/*!
*/
AsTask	*AsTask::CheckExist(Uint32 sid, AsTask *node)
{
	AsTask	*st, *ft;
	if (node == NULL) {
		for(st = m_pTaskSystem->m_pRoot; st != NULL; st = st->m_pNext) {
			ft = st->_checkExistSub(sid);
			if (ft != NULL) {
				return ft;
			}
		}
	} else {
		return node->_checkExistSub(sid);
	}
	return NULL;
}

/*!
*/
void AsTask::KillChild()
{
	AsTask	*st, *st_next;
	st = GetChild();
	while (st != NULL) {
		st_next = st->GetNext();
		st->Kill();
		st = st_next;
	}
}

/*!
*/
void AsTask::KillFamily()
{
	AsTask	*st, *st_next;
	st = GetChild();
	while (st != NULL) {
		st_next = st->GetNext();
		st->KillFamily();
		st->Kill();
		st = st_next;
	}
}

/*!
*/
void AsTask::Pre()
{
	return;
}

/*!
*/
void AsTask::PreOut()
{
	return;
}

/*!
*/
void AsTask::Main()
{
	return;
}

/*!
*/
void AsTask::MainOut()
{
	return;
}

/*!
*/
void AsTask::Draw()
{
	return;
}

void AsTask::DrawOut()
{
	return;
}

/*!
*/
void AsTask::Post()
{
	return;
}

/*!
*/
void AsTask::PostOut()
{
	return;
}

/*!
*/
void AsTask::CleanUpEntry()
{
	AsTask	*ct, *nt;
	AsTaskSystem	*pSystem;
	ct = this;
	pSystem = m_pTaskSystem;
	while (ct != NULL) {
		if (!(ct->m_Status & STAT_Dead)) {
			if (ct->m_pChild != NULL) {
				ct->m_pChild->CleanUpEntry();
			}
			ct = ct->m_pNext;
		} else {
			nt = ct->m_pNext;
			if(!ct->CheckKill()) {
				ct->Kill();
			}
			delete ct;
			ct = nt;
		}
	}
}

/*!
*/
void AsTask::Delete()
{
	AsTask	*st, *st_next;
	st = m_pChild;
	while (st != NULL) {
		st_next = st->m_pNext;
		if(!st->CheckKill()) {
			st->Kill();
		}
		st->Delete();
		st = st_next;
	}
	AsAssert( m_pChild == NULL );
	m_pChild = NULL;

	if (m_pPrev != NULL) {
		if (m_pPrev->m_pChild == this) {
			m_pPrev->m_pChild = m_pNext;
		} else {
			m_pPrev->m_pNext = m_pNext;
		}
	} else {
		m_pTaskSystem->m_pRoot = m_pNext;
	}
	if (m_pNext != NULL) {
		m_pNext->m_pPrev = m_pPrev;
	}
	m_Status |= STAT_Delete;
	delete this;
}


void AsTask::CleanUpEntry2()
{
	AsTaskSystem *system = m_pTaskSystem;

	if ( m_Status & STAT_Dead ) {
		Delete();
		return;
	}

	AsTask *st, *st_next;
	st = m_pChild;
	while(st != NULL) {
		st_next = st->m_pNext;
		st->CleanUpEntry2();
		st = st_next;
	}
}

/*!
*/
void AsTask::PreEntry()
{
	AsTask *ct = this;
	bool cf;
	while (ct != NULL) {
		if (!(ct->m_Status & STAT_Dead)) {
			cf = !(ct->m_Status & STAT_SkipPre);

			/* Pre */
			if (cf) {
				ct->Pre();		/* Pre */
			}
			if (ct->m_pChild != NULL &&
			   !(ct->m_Status & (STAT_SkipPreChild | STAT_Dead))) {
				ct->m_pChild->PreEntry();
			}
			/* PreOut */
			if (cf && !(ct->m_Status & STAT_Dead)) {
				ct->PreOut();
			}
		}
		ct = ct->m_pNext;
	}
}

/*!
*/
void AsTask::MainEntry()
{
	AsTask *ct = this;
	bool cf;
	while (ct != NULL) {
		if (!(ct->m_Status & STAT_Dead)) {
			cf = !(ct->m_Status & STAT_SkipMain);

			/* Main */
			if (cf) {
				ct->Main();
			}

			if (ct->m_pChild != 0 &&
			   !(ct->m_Status & (STAT_SkipMainChild | STAT_Dead))) {
				ct->m_pChild->MainEntry();
			}
			/* MainOut */
			if (cf && !(ct->m_Status & STAT_Dead)) {
				ct->MainOut();
			}
		}
		ct = ct->m_pNext;
	}
}

/*!
*/
void AsTask::DrawEntry(Uint32 rmode)
{
	AsTask *ct = this;
	bool cf;
	Uint32 keep_cond;
	while (ct != NULL) {
		if (!(ct->m_Status & STAT_Dead)) {
			cf = !(ct->m_Status & rmode);

			/* Draw */
			if (cf) {
				keep_cond = ct->m_Status & STAT_DRAWMASK;
				ct->m_Status &= ~STAT_DRAWMASK;
				ct->m_Status |= rmode;

				ct->Draw();

				ct->m_Status &= ~STAT_DRAWMASK;
				ct->m_Status |= keep_cond;
			}

			if (ct->m_pChild != NULL &&
			   !(ct->m_Status & (STAT_SkipDrawChild | STAT_Dead))) {
				ct->m_pChild->DrawEntry(rmode);
			}

			/* DrawOut */
			if (cf && !(ct->m_Status & STAT_Dead)) {
				keep_cond = ct->m_Status & STAT_DRAWMASK;
				ct->m_Status &= ~STAT_DRAWMASK;
				ct->m_Status |= rmode;

				ct->DrawOut();

				ct->m_Status &= ~STAT_DRAWMASK;
				ct->m_Status |= keep_cond;
			}
		}
		ct = ct->m_pNext;
	}
}

/*!
 */
void AsTask::DrawEntryOne(Uint32 rmode)
{
	bool	cf;
	Uint32	keep_cond;

	if (!(m_Status & STAT_Dead)) {
		cf = !(m_Status & rmode);

		/* Draw */
		if (cf) {
			keep_cond = m_Status & STAT_DRAWMASK;
			m_Status &= ~STAT_DRAWMASK;
			m_Status |= rmode;

			Draw();

			m_Status &= ~STAT_DRAWMASK;
			m_Status |= keep_cond;
		}

		/* DrawEntry */
		if (m_pChild != NULL &&
		   !(m_Status & (STAT_SkipDrawChild | STAT_Dead))) {
			m_pChild->DrawEntry(rmode);
		}

		/* DrawOut */
		if (cf && !(m_Status & STAT_Dead)) {
			DrawOut();	/* ﾃｯ`ﾃ｢ﾃ甘ｨIﾃｳﾏ */
		}
	}
}

void AsTask::PostEntry()
{
	AsTask *ct = this;
	bool cf;
	while (ct != NULL) {
		if (!(ct->m_Status & STAT_Dead)) {
			cf = !(ct->m_Status & STAT_SkipPost);

			/* Post */
			if (cf) {
				ct->Post();
			}

			if (ct->m_pChild != 0 &&
			   !(ct->m_Status & (STAT_SkipPostChild | STAT_Dead))) {
				ct->m_pChild->PostEntry();
			}
			/* PostOut */
			if(cf && !(ct->m_Status & STAT_Dead)) {
				ct->PostOut();
			}
		}
		ct = ct->m_pNext;
	}
}

/* end of file */


