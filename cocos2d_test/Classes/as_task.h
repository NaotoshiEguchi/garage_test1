#ifndef _AS_TASK_H_
#define _AS_TASK_H_

#include "am_base.h"


#define TASK_SAFE_KILL(_task_) if ((_task_) != NULL) {(_task_)->Kill(); (_task_) = NULL;} 

class AsTask;


/*!
	\class AsTaskSystem
*/
class AsTaskSystem : public AmBase 
{
	friend	class AsTask;

public:
	AsTaskSystem();
	~AsTaskSystem();

public:
	void ExecPre();
	void ExecMain();
	void ExecDraw();
	void ExecPost();

	void ExecCleanUp();
	void ExecCleanUp2();

	AsTask *GetRootTask();

private:
	Uint32 m_TaskID;
	AsTask *m_pRoot;
};

/*!
*/
class AsTask : public AmBase
{
	friend class AsTaskSystem;

private:
	enum {
		STAT_Dead			= (1 << 31),
		STAT_Delete			= (1 << 30),	
		STAT_SkipPre		= (1 << 27),
		STAT_SkipMain		= (1 << 26),
		STAT_SkipPost		= (1 << 25),

		STAT_SkipPreChild	= (1 << 23),
		STAT_SkipMainChild	= (1 << 22),
		STAT_SkipDrawChild	= (1 << 21),
		STAT_SkipPostChild	= (1 << 20),	


		STAT_NormalDraw		= (1 << 15),


		STAT_SkipDraw		= (STAT_NormalDraw),
		STAT_SleepChild		= (STAT_SkipPreChild |
							   STAT_SkipMainChild |
							   STAT_SkipDrawChild |
							   STAT_SkipPostChild),
		STAT_PauseChild		= (STAT_SkipPreChild |
							   STAT_SkipMainChild |
							   STAT_SkipPostChild),
		STAT_Sleep			= (STAT_SkipPre |
							   STAT_SkipMain |
							   STAT_SkipDraw |
							   STAT_SkipPost |
							   STAT_SleepChild),
		STAT_Pause			= (STAT_SkipPre |
							   STAT_SkipMain |
							   STAT_SkipPost |
							   STAT_PauseChild),

		STAT_DRAWMASK		= (STAT_NormalDraw),
	};

private:
	Uint32	m_ID;
	Uint32	m_Status;

	AsTask	*m_pChild;
	AsTask	*m_pNext;
	AsTask	*m_pPrev;
	AsTask	*m_pParent;	

	AsTaskSystem	*m_pTaskSystem;


public:
  static Sint32 s_TaskNumber;
  static Sint32 GetTaskNumber();

private:
	void	_setCondition(Uint32 c)	{ m_Status = c; }

private:
	void	PreEntry();
	void	MainEntry();
	void	DrawEntry(Uint32 rmode);
	void	PostEntry();

	void	CleanUpEntry();
	void	CleanUpEntry2();
	void	Delete();
	void	DeleteFamily();

	void	DrawEntryOne(Uint32 rmode);

protected:
	virtual void	Pre();	
	virtual void	PreOut();
	virtual void	Main();	
	virtual void	MainOut();
	virtual void	Draw();
	virtual void	DrawOut();
	virtual void	Post();	
	virtual void	PostOut();
	
public:
	AsTask(AsTaskSystem *pSystem);
	AsTask(AsTask *pParent);	

protected:
	virtual	~AsTask();

private:
	AsTask	*_searchSub(Uint32 sid);
	AsTask	*_checkExistSub(Uint32 sid);

public:
	AsTask	*Search(Uint32 sid, AsTask *node = NULL);	
	AsTask	*CheckExist(Uint32 sid, AsTask *node = NULL);

public:
	Uint32	GetId() const { return m_ID; }
	Uint32	GetCondition() const { return m_Status; }
	AsTask	*GetChild() const { return m_pChild; }
	AsTask	*GetNext() const { return m_pNext; }
	AsTask	*GetParent() const { return m_pParent; }

public:
	virtual	void	Kill()	{ m_Status |= STAT_Dead; }
	void	KillChild();
	void	KillFamily();


	void	Sleep()			{ m_Status |= STAT_Sleep; }
	void	Awake()			{ m_Status &= ~STAT_Sleep; }
	void	SleepChild()	{ m_Status |= STAT_SleepChild; }
	void	AwakeChild()	{ m_Status &= ~STAT_SleepChild; }
	void	Pause()			{ m_Status |= STAT_Pause; }
	void	UnPause()		{ m_Status &= ~STAT_Pause; }
	void	PauseChild()	{ m_Status |= STAT_PauseChild; }
	void	UnPauseChild()	{ m_Status &= ~STAT_PauseChild; }
	void	StopPre()		{ m_Status |= STAT_SkipPre; }
	void	ResumePre()		{ m_Status &= ~STAT_SkipPre; }
	void	StopMain()		{ m_Status |= STAT_SkipMain; }
	void	ResumeMain()	{ m_Status &= ~STAT_SkipMain; }
	void	StopDraw()		{ m_Status |= STAT_SkipDraw; }
	void	ResumeDraw()	{ m_Status &= ~STAT_SkipDraw; }
	void	StopPost()		{ m_Status |= STAT_SkipPost; }
	void	ResumePost()	{ m_Status &= ~STAT_SkipPost; }
	void	StopPreChild()		{ m_Status |= STAT_SkipPreChild; }
	void	ResumePreChild()	{ m_Status &= ~STAT_SkipPreChild; }
	void	StopMainChild()		{ m_Status |= STAT_SkipMainChild; }
	void	ResumeMainChild()	{ m_Status &= ~STAT_SkipMainChild; }
	void	StopDrawChild()		{ m_Status |= STAT_SkipDrawChild; }
	void	ResumeDrawChild()	{ m_Status &= ~STAT_SkipDrawChild; }
	void	StopPostChild()		{ m_Status |= STAT_SkipPostChild; }
	void	ResumePostChild()	{ m_Status &= ~STAT_SkipPostChild; }

public:
	bool	CheckKill() const {return (m_Status & STAT_Dead) != 0;}
	bool	CheckSleep() const {return (m_Status & STAT_Sleep) == STAT_Sleep;}
	bool	CheckSleepChild() const {return (m_Status & STAT_SleepChild) == STAT_SleepChild;}
	bool	CheckPause() const {return (m_Status & STAT_Pause) == STAT_Pause;}
	bool	CheckPauseChild() const {return (m_Status & STAT_PauseChild) == STAT_PauseChild;}
	bool	CheckStopPre() const {return (m_Status & STAT_SkipPre) != 0;}
	bool	CheckStopMain() const {return (m_Status & STAT_SkipMain) != 0;}
	bool	CheckStopDraw() const {return (m_Status & STAT_SkipDraw) != 0;}
	bool	CheckStopPost() const {return (m_Status & STAT_SkipPost) != 0;}
	bool	CheckStopPreChild() const {return (m_Status & STAT_SkipPreChild) != 0;}
	bool	CheckStopMainChild() const {return (m_Status & STAT_SkipMainChild) != 0;}
	bool	CheckStopDrawChild() const {return (m_Status & STAT_SkipDrawChild) != 0;}
	bool	CheckStopPostChild() const {return (m_Status & STAT_SkipPostChild) != 0;}
};

#endif /* _TASK_H_ */

/* end of file */


