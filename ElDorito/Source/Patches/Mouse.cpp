#include "Mouse.hpp"
#include "../ElDorito.hpp"
#include "../Patch.hpp"
 
namespace
{
	void AimAssistHook();
	uint32_t DualAimAssistHook(uint32_t unitObject, short weaponIndex);
}
 
namespace Patches::Mouse
{
	void ApplyAll()
	{
		Hook(0x18AA17, AimAssistHook).Apply();
		Hook(0x18ABAB, DualAimAssistHook, HookFlags::IsCall).Apply();
	}
}
 
namespace
{
	__declspec(naked) void AimAssistHook()
	{
		__asm
		{
			mov edx, 0x244DE98
			mov edx, [edx]
			test edx, edx
			jnz controller
 
			movss xmm0, dword ptr[ebx + 0x388]
			mov edx, 0x58AA1F
			jmp edx
 
		controller:
			movss xmm0, dword ptr[ebx + 0x388]
			mov edx, 0x58AA1F
			jmp edx
		}
	}
 
	uint32_t DualAimAssistHook(uint32_t unitObject, short weaponIndex)
	{
		typedef uint32_t(*UnitGetWeaponPtr)(uint32_t unitObject, short weaponIndex);
		auto UnitGetWeapon = reinterpret_cast<UnitGetWeaponPtr>(0xB454D0);
		return UnitGetWeapon(unitObject, weaponIndex);
	}
}
