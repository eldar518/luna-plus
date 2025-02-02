#pragma once
#include "Action.h"

namespace Trigger
{
	class CActionSetFlag :
		public CAction
	{
	public:
		virtual void DoAction();
		static CAction* Clone()
		{
			return new CActionSetFlag;
		}
	};
}