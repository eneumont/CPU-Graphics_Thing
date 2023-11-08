#pragma once
#include "Components/Component.h"

namespace nc {
	class RotateComponent : Component {
	public:
		CLASS_DECLARATION(RotateComponent)

		bool Initialize() override;
	};
}