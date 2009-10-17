// -*- C++ -*-
//=============================================================================
/**
 *  @file   Codeset_Symbols.h
 *
 *  $Id: Codeset_Symbols.h 80826 2008-03-04 14:51:23Z wotte $
 *
 * Symbolic names for codeset ids.
 *
 *  @author Dale Wilson (wilson_d@ociweb.com)
 */
//=============================================================================
#ifndef CODESET_SYMBOLS_H
#define CODESET_SYMBOLS_H
// These numbers are assigned by the OpenGroup, a database is
// available at
//
// ftp://ftp.opengroup.org/pub/code_set_registry/
//
// Alas, the database is in a semi-regular text file -- difficult to use.
// The following C/C++-friendly version of the codeset ids was captured
// from Version 1.2g of the registry.
//
#define ACE_CODESET_ID_ISO_8859_1 0x00010001U
#define ACE_CODESET_ID_ISO_8859_2 0x00010002U
#define ACE_CODESET_ID_ISO_8859_3 0x00010003U
#define ACE_CODESET_ID_ISO_8859_4 0x00010004U
#define ACE_CODESET_ID_ISO_8859_5 0x00010005U
#define ACE_CODESET_ID_ISO_8859_6 0x00010006U
#define ACE_CODESET_ID_ISO_8859_7 0x00010007U
#define ACE_CODESET_ID_ISO_8859_8 0x00010008U
#define ACE_CODESET_ID_ISO_8859_9 0x00010009U
#define ACE_CODESET_ID_ISO_8859_10 0x0001000AU
#define ACE_CODESET_ID_ISO_8859_15 0x0001000FU
#define ACE_CODESET_ID_ISO_646 0x00010020U
#define ACE_CODESET_ID_ISO_UCS_2_LEVEL_1 0x00010100U
#define ACE_CODESET_ID_ISO_UCS_2_LEVEL_2 0x00010101U
#define ACE_CODESET_ID_ISO_UCS_2_LEVEL_3 0x00010102U
#define ACE_CODESET_ID_ISO_UCS_4_LEVEL_1 0x00010104U
#define ACE_CODESET_ID_ISO_UCS_4_LEVEL_2 0x00010105U
#define ACE_CODESET_ID_ISO_UCS_4_LEVEL_3 0x00010106U
#define ACE_CODESET_ID_ISO_UTF_8 0x00010108U
#define ACE_CODESET_ID_ISO_UTF_16 0x00010109U
#define ACE_CODESET_ID_JIS_X0201 0x00030001U
#define ACE_CODESET_ID_JIS_X0208_1978 0x00030004U
#define ACE_CODESET_ID_JIS_X0208_1983 0x00030005U
#define ACE_CODESET_ID_JIS_X0208_1990 0x00030006U
#define ACE_CODESET_ID_JIS_X0212 0x0003000AU
#define ACE_CODESET_ID_JIS_EUCJP 0x00030010U
#define ACE_CODESET_ID_KS_C5601 0x00040001U
#define ACE_CODESET_ID_KS_C5657 0x00040002U
#define ACE_CODESET_ID_KS_EUCKR 0x0004000AU
#define ACE_CODESET_ID_CNS_11643_1986 0x00050001U
#define ACE_CODESET_ID_CNS_11643_1992 0x00050002U
#define ACE_CODESET_ID_CNS_EUCTW_1991 0x0005000AU
#define ACE_CODESET_ID_CNS_EUCTW_1993 0x00050010U
#define ACE_CODESET_ID_TIS_620_25290X000B0001U
#define ACE_CODESET_ID_TTB_CCDC 0x000D0001U
#define ACE_CODESET_ID_OSF_JAPANESE_UJIS 0x05000010U
#define ACE_CODESET_ID_OSF_JAPANESE_SJIS_1 0x05000011U
#define ACE_CODESET_ID_OSF_JAPANESE_SJIS_2 0x05000012U
#define ACE_CODESET_ID_XOPEN_UTF_8 0x05010001U
#define ACE_CODESET_ID_JVC_EUCJP 0x05020001U
#define ACE_CODESET_ID_JVC_SJIS 0x05020002U
#define ACE_CODESET_ID_DEC_KANJI 0x10000001U
#define ACE_CODESET_ID_SUPER_DEC_KANJI 0x10000002U
#define ACE_CODESET_ID_DEC_SHIFT_JIS 0x10000003U
#define ACE_CODESET_ID_HP_ROMAN8 0x10010001U
#define ACE_CODESET_ID_HP_KANA8 0x10010002U
#define ACE_CODESET_ID_HP_ARABIC8 0x10010003U
#define ACE_CODESET_ID_HP_GREEK8 0x10010004U
#define ACE_CODESET_ID_HP_HEBREW8 0x10010005U
#define ACE_CODESET_ID_HP_TURKISH8 0x10010006U
#define ACE_CODESET_ID_HP15CN 0x10010007U
#define ACE_CODESET_ID_HP_BIG5 0x10010008U
#define ACE_CODESET_ID_HP_JAPANESE15__SJIS_ 0x10010009U
#define ACE_CODESET_ID_HP_SJISHI 0x1001000AU
#define ACE_CODESET_ID_HP_SJISPC 0x1001000BU
#define ACE_CODESET_ID_HP_UJIS 0x1001000CU
#define ACE_CODESET_ID_IBM_037 0x10020025U
#define ACE_CODESET_ID_IBM_273 0x10020111U
#define ACE_CODESET_ID_IBM_277 0x10020115U
#define ACE_CODESET_ID_IBM_278 0x10020116U
#define ACE_CODESET_ID_IBM_280 0x10020118U
#define ACE_CODESET_ID_IBM_282 0x1002011AU
#define ACE_CODESET_ID_IBM_284 0x1002011CU
#define ACE_CODESET_ID_IBM_285 0x1002011DU
#define ACE_CODESET_ID_IBM_290 0x10020122U
#define ACE_CODESET_ID_IBM_297 0x10020129U
#define ACE_CODESET_ID_IBM_300 0x1002012CU
#define ACE_CODESET_ID_IBM_301 0x1002012DU
#define ACE_CODESET_ID_IBM_420 0x100201A4U
#define ACE_CODESET_ID_IBM_424 0x100201A8U
#define ACE_CODESET_ID_IBM_437 0x100201B5U
#define ACE_CODESET_ID_IBM_500 0x100201F4U
#define ACE_CODESET_ID_IBM_833 0x10020341U
#define ACE_CODESET_ID_IBM_834 0x10020342U
#define ACE_CODESET_ID_IBM_835 0x10020343U
#define ACE_CODESET_ID_IBM_836 0x10020344U
#define ACE_CODESET_ID_IBM_837 0x10020345U
#define ACE_CODESET_ID_IBM_838 0x10020346U
#define ACE_CODESET_ID_IBM_839 0x10020347U
#define ACE_CODESET_ID_IBM_850 0x10020352U
#define ACE_CODESET_ID_IBM_852 0x10020354U
#define ACE_CODESET_ID_IBM_855 0x10020357U
#define ACE_CODESET_ID_IBM_856 0x10020358U
#define ACE_CODESET_ID_IBM_857 0x10020359U
#define ACE_CODESET_ID_IBM_861 0x1002035DU
#define ACE_CODESET_ID_IBM_862 0x1002035EU
#define ACE_CODESET_ID_IBM_863 0x1002035FU
#define ACE_CODESET_ID_IBM_864 0x10020360U
#define ACE_CODESET_ID_IBM_866 0x10020362U
#define ACE_CODESET_ID_IBM_868 0x10020364U
#define ACE_CODESET_ID_IBM_869 0x10020365U
#define ACE_CODESET_ID_IBM_870 0x10020366U
#define ACE_CODESET_ID_IBM_871 0x10020367U
#define ACE_CODESET_ID_IBM_874 0x1002036AU
#define ACE_CODESET_ID_IBM_875 0x1002036BU
#define ACE_CODESET_ID_IBM_880 0x10020370U
#define ACE_CODESET_ID_IBM_891 0x1002037BU
#define ACE_CODESET_ID_IBM_896 0x10020380U
#define ACE_CODESET_ID_IBM_897 0x10020381U
#define ACE_CODESET_ID_IBM_903 0x10020387U
#define ACE_CODESET_ID_IBM_904 0x10020388U
#define ACE_CODESET_ID_IBM_918 0x10020396U
#define ACE_CODESET_ID_IBM_921 0x10020399U
#define ACE_CODESET_ID_IBM_922 0x1002039AU
#define ACE_CODESET_ID_IBM_926 0x1002039EU
#define ACE_CODESET_ID_IBM_927 0x1002039FU
#define ACE_CODESET_ID_IBM_928 0x100203A0U
#define ACE_CODESET_ID_IBM_929 0x100203A1U
#define ACE_CODESET_ID_IBM_930 0x100203A2U
#define ACE_CODESET_ID_IBM_932 0x100203A4U
#define ACE_CODESET_ID_IBM_933 0x100203A5U
#define ACE_CODESET_ID_IBM_934 0x100203A6U
#define ACE_CODESET_ID_IBM_935 0x100203A7U
#define ACE_CODESET_ID_IBM_936 0x100203A8U
#define ACE_CODESET_ID_IBM_937 0x100203A9U
#define ACE_CODESET_ID_IBM_938 0x100203AAU
#define ACE_CODESET_ID_IBM_939 0x100203ABU
#define ACE_CODESET_ID_IBM_941 0x100203ADU
#define ACE_CODESET_ID_IBM_942 0x100203AEU
#define ACE_CODESET_ID_IBM_943 0x100203AFU
#define ACE_CODESET_ID_IBM_946 0x100203B2U
#define ACE_CODESET_ID_IBM_947 0x100203B3U
#define ACE_CODESET_ID_IBM_948 0x100203B4U
#define ACE_CODESET_ID_IBM_949 0x100203B5U
#define ACE_CODESET_ID_IBM_950 0x100203B6U
#define ACE_CODESET_ID_IBM_951 0x100203B7U
#define ACE_CODESET_ID_IBM_955 0x100203BBU
#define ACE_CODESET_ID_IBM_964 0x100203C4U
#define ACE_CODESET_ID_IBM_970 0x100203CAU
#define ACE_CODESET_ID_IBM_1006 0x100203EEU
#define ACE_CODESET_ID_IBM_1025 0x10020401U
#define ACE_CODESET_ID_IBM_1026 0x10020402U
#define ACE_CODESET_ID_IBM_1027 0x10020403U
#define ACE_CODESET_ID_IBM_1040 0x10020410U
#define ACE_CODESET_ID_IBM_1041 0x10020411U
#define ACE_CODESET_ID_IBM_1043 0x10020413U
#define ACE_CODESET_ID_IBM_1046 0x10020416U
#define ACE_CODESET_ID_IBM_1047 0x10020417U
#define ACE_CODESET_ID_IBM_1088 0x10020440U
#define ACE_CODESET_ID_IBM_1097 0x10020449U
#define ACE_CODESET_ID_IBM_1098 0x1002044AU
#define ACE_CODESET_ID_IBM_1112 0x10020458U
#define ACE_CODESET_ID_IBM_1114 0x1002045AU
#define ACE_CODESET_ID_IBM_1115 0x1002045BU
#define ACE_CODESET_ID_IBM_1122 0x10020462U
#define ACE_CODESET_ID_IBM_1250 0x100204E2U
#define ACE_CODESET_ID_IBM_1251 0x100204E3U
#define ACE_CODESET_ID_IBM_1252 0x100204E4U
#define ACE_CODESET_ID_IBM_1253 0x100204E5U
#define ACE_CODESET_ID_IBM_1254 0x100204E6U
#define ACE_CODESET_ID_IBM_1255 0x100204E7U
#define ACE_CODESET_ID_IBM_1256 0x100204E8U
#define ACE_CODESET_ID_IBM_1257 0x100204E9U
#define ACE_CODESET_ID_IBM_1380 0x10020564U
#define ACE_CODESET_ID_IBM_1381 0x10020565U
#define ACE_CODESET_ID_IBM_1383 0x10020567U
#define ACE_CODESET_ID_IBM_4396 0x1002112CU
#define ACE_CODESET_ID_IBM_4946 0x10021352U
#define ACE_CODESET_ID_IBM_4948 0x10021354U
#define ACE_CODESET_ID_IBM_4951 0x10021357U
#define ACE_CODESET_ID_IBM_4952 0x10021358U
#define ACE_CODESET_ID_IBM_4953 0x10021359U
#define ACE_CODESET_ID_IBM_4960 0x10021360U
#define ACE_CODESET_ID_IBM_4964 0x10021364U
#define ACE_CODESET_ID_IBM_4965 0x10021365U
#define ACE_CODESET_ID_IBM_5026 0x100213A2U
#define ACE_CODESET_ID_IBM_5031 0x100213A7U
#define ACE_CODESET_ID_IBM_5035 0x100213ABU
#define ACE_CODESET_ID_IBM_5048 0x100213B8U
#define ACE_CODESET_ID_IBM_5049 0x100213B9U
#define ACE_CODESET_ID_IBM_5067 0x100213CBU
#define ACE_CODESET_ID_IBM_8612 0x100221A4U
#define ACE_CODESET_ID_IBM_9025 0x10022341U
#define ACE_CODESET_ID_IBM_9026 0x10022342U
#define ACE_CODESET_ID_IBM_9030 0x10022346U
#define ACE_CODESET_ID_IBM_9056 0x10022360U
#define ACE_CODESET_ID_IBM_9066 0x1002236AU
#define ACE_CODESET_ID_IBM_9125 0x100223A5U
#define ACE_CODESET_ID_IBM_25426 0x10026352U
#define ACE_CODESET_ID_IBM_25432 0x10026358U
#define ACE_CODESET_ID_IBM_1042 0x10026412U
#define ACE_CODESET_ID_IBM_28709 0x10027025U
#define ACE_CODESET_ID_IBM_33624 0x10028358U
#define ACE_CODESET_ID_IBM_33722 0x100283BAU
#define ACE_CODESET_ID_HTCSJIS 0x10030001U
#define ACE_CODESET_ID_HTCUJIS 0x10030002U
#define ACE_CODESET_ID_FUJITSU_U90 0x10040001U
#define ACE_CODESET_ID_FUJITSU_S90 0x10040002U
#define ACE_CODESET_ID_FUJITSU_R90 0x10040003U
#define ACE_CODESET_ID_EBCDIC_ASCII_AND_JEF 0x10040004U
#define ACE_CODESET_ID_EBCDIC_KATAKANA_AND_JEF 0x10040005U
#define ACE_CODESET_ID_EBCDIC_JAPANESE_ENGLISH_AND_JEF 0x10040006U
#define ACE_CODESET_ID_TAO_BACKWARD_COMPATIBLE 0xf54414F0U
#endif // CODESET_SYMBOLS_H

