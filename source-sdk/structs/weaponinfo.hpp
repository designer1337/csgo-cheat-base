#pragma once

class weapon_info_t {
public:
	char pad_0x0000[0x4]; //0x0000
	char* m_szWeaponName; //0x0004
	char pad_0x0008[0xC]; //0x0008
	__int32 m_iMaxClip; //0x0014
	char pad_0x0018[0xC]; //0x0018
	__int32 m_iMaxReservedAmmo; //0x0024
	char pad_0x0028[0x4]; //0x0028
	char* m_szWeaponMdlPath; //0x002C
	char* m_szWeaponMdlPath2; //0x0030
	char* m_szDroppedWeaponMdlPath; //0x0034
	char* m_szDefaultClip; //0x0038
	char pad_0x003C[0x44]; //0x003C
	char* m_szBulletType; //0x0080
	char pad_0x0084[0x4]; //0x0084
	char* m_szHudName; //0x0088
	char* m_szWeaponName2; //0x008C
	char pad_0x0090[0x38]; //0x0090
	__int32 m_iWeaponType; //0x00C8
	__int32 m_iWeaponType2; //0x00CC
	__int32 m_iWeaponPrice; //0x00D0
	__int32 m_iWeaponReward; //0x00D4
	char* m_szWeaponType; //0x00D8
	float m_flUnknownFloat0; //0x00DC
	char pad_0x00E0[0xC]; //0x00E0
	unsigned char m_ucFullAuto; //0x00EC
	char pad_0x00ED[0x3]; //0x00ED
	__int32 m_iWeaponDamage; //0x00F0
	float m_flArmorRatio; //0x00F4
	__int32 m_iBullets; //0x00F8
	float m_flPenetration; //0x00FC
	char pad_0x0100[0x8]; //0x0100
	float m_flWeaponRange; //0x0108
	float m_flRangeModifier; //0x010C
	float m_flThrowVelocity; //0x0110
	char pad_0x0114[0xC]; //0x0114
	unsigned char m_ucHasSilencer; //0x0120
	char pad_0x0121[0xF]; //0x0121
	float m_flMaxSpeed; //0x0130
	float m_flMaxSpeed2; //0x0134
	float m_flAttackMoveSpeedFactor; //0x0138
	float m_flSpread; //0x013C
	float m_flSpreadAlt; //0x0140
	float m_flInaccuracyCrouch; //0x0144
	float m_flInaccuracyCrouchAlt; //0x0148
	float m_flInaccuracyStand; //0x014C
	float m_flInaccuracyStandAlt; //0x0150
	float m_flInaccuracyJump; //0x0154
	float m_flInaccuracyJumpAlt; //0x0158
	char pad_0x015C[0x28]; //0x015C
	__int32 m_iRecoilSeed; //0x0184
	char pad_0x0188[0x68]; //0x0188
	char* m_szWeaponTracesType; //0x01F0
	char pad_0x01F4[0x648]; //0x01F4
};