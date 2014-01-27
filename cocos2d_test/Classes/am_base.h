#ifndef _AM_BASE_H_
#define _AM_BASE_H_

#include "am_define.h"

/*!
	\class AmBase
*/
class AmBase
{
public:
	AmBase() : m_Status(0) {}

	void SetTag(Uint32) {}
	void SetTag(const char *pTag)
	{
		Sint32 i;
		char *pDst = m_aTag;
		for (i = 0; i < TAG_MAX - 1 && *pTag != '\0'; i++) {
			*pDst++ = *pTag++;
		}
		*pDst = '\0';
	}

	bool CheckBusy() const {return (m_Status & STATUS_BUSY) != 0;}
	bool CheckReady() const {return (m_Status & STATUS_READY) != 0;}
	bool CheckFinish() const {return (m_Status & STATUS_FINISH) != 0;}

	void SetBusy() {m_Status |= STATUS_BUSY;}
	void SetReady() {m_Status |= STATUS_READY;}
	void SetFinish() {m_Status |= STATUS_FINISH;}

private:
	static const Uint32 TAG_MAX = 8;
	char m_aTag[TAG_MAX];

	enum {
		STATUS_NONE = 0,
		STATUS_BUSY = (1 << 0),
		STATUS_READY = (1 << 1),
		STATUS_FINISH = (1 << 2),
	};

	Uint32 m_Status;
};

#endif /* _AM_BASE_H_ */

/* end of file */
