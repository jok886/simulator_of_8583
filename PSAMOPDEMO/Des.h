// Des.h: interface for the CDes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DES_H__41DBBDAC_CF1C_4FF1_A4FD_33EFFFCF9FE9__INCLUDED_)
#define AFX_DES_H__41DBBDAC_CF1C_4FF1_A4FD_33EFFFCF9FE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char byte;
class CDes  
{
private:
	void cipher(byte *input, byte *output, byte mode);
	void rotate(byte* ptr, byte times);
	void function_rk(byte *input, byte *output, byte *key);
	void do_ip(byte *input, byte *output, byte *table);
	byte ip_table[64];
	byte inv_ip_table[64];
	byte exp_table[48];
	byte perm_table[48];
	byte perm_choice1_C[28];
	byte perm_choice1_D[28];
	byte perm_choice2[48];
	byte shifts_table[16];
	byte sel_table[512];
	byte bitmapx[64];
	byte perm_keys[16][6];
	byte key[8];
	byte card_data[9];
	byte card_data1[9];
	
	void gen_keys();

public:
	void EnCode( byte *dg,byte *out,const byte *key_ptr);
	void DeCode( byte *dg,byte *out,const byte *key_ptr);
	CDes();
	virtual ~CDes();

};

#endif // !defined(AFX_DES_H__41DBBDAC_CF1C_4FF1_A4FD_33EFFFCF9FE9__INCLUDED_)
