

#ifndef _SPEED_CHARM_POLICY_H_
#define _SPEED_CHARM_POLICY_H_




#define SC_POLICY_OUT_NORMAL 0


#define SC_POLICY_ERROR_FOPEN -1


#define SC_POLICY_ERROR_SC_INIT -2


#define SC_POLICY_ERROR_INVALID_VERSION -3


#define SC_POLICY_ERROR_ALLOC -4


#define SC_POLICY_FILE_ERROR_POLICY_END SC_POLICY_ERROR_ALLOC





#define SC_POLICY_ERROR_ENTRY_MAGIC_NUM -5


#define SC_POLICY_ERROR_VERSION -6


#define SC_POLICY_ERROR_USER -7


#define SC_POLICY_ERROR_OS_COMMENT -8


#define SC_POLICY_ERROR_COMMENT_MAIN -9


#define SC_POLICY_ERROR_BEG -10


#define SC_POLICY_ERROR_END -11


#define SC_POLICY_ERROR_CHECK(error_code) (error_code < SC_POLICY_OUT_NORMAL)


#define SC_POLICY_ERROR_IDENTIFY_START(offset) (SC_POLICY_ERROR_END - offset)





#define SC_POLICY_OS_STR_SIZE 5


#define SC_POLICY_OS_ANOTHER_COMMENT_SIZE(max_comment_size) \
    (max_comment_size - SC_POLICY_OS_STR_SIZE)





#define SC_POLICY_NO_LOCK_KEY 0





#define SC_POLICY_FILE_NAME_MAX (1 << 5)


#define SC_POLICY_FILE_FORMAT_MAX ((1 << 2) + 1)


#define SC_POLICY_FILE_FORMAT_NAME(low) ".""sc" #low




#define SC_ZSTD_COMPRESS_ID 0


#define SC_ZIP_COMPRESS_ID 1


#define SC_7ZIP_COMPRESS_ID 2


#define SC_POLICY_REQUIRE_BEG_CHUNK "BEG"


#define SC_POLICY_REQUIRE_END_CHUNK "END"



#define SC_POLICY_REQUIRE_SC_ENTRY_MAGIC_NUM(sc_magic_num) sc_magic_num

#define SC_POLICY_REQUIRE_SC_ENTRY_MAGIC_NUM_POS(pos) (pos == 0)


#define SC_POLICY_REQUIRE_CHECK_END_NEXT(end_chunk_next) (end_chunk_next == EOF)


#define SC_POLICY_BEG_CHUNK_POS(magic_num_pos, beg_pos, end_pos) (magic_num_pos < beg_pos && beg_pos < end_pos)


#define SC_POLICY_REQUIRE_VERSION_BLOCK(ver) ver


#define SC_POLICY_REQUIRE_USER_BLOCK(usr) usr


#define SC_POLICY_REQUIRE_COMMENT_BLOCK(com) com





typedef uint64_t sc_size;


typedef uint64_t sc_uint64;


typedef uint32_t sc_uint;


typedef uint16_t sc_ushort;


typedef uint8_t sc_ubyte;


typedef int64_t sc_int64;


typedef int32_t sc_int;


typedef int16_t sc_short;


typedef char sc_byte;


typedef FILE * SC_FILE;


typedef long sc_err_t;


#define SC_POLICY_SC_UINT_8_BITS 8


#define SC_POLICY_SET_SC_VERSION(ver) (ver)


#define SC_POLICY_BASE_MAJOR_VERSION SC_POLICY_SET_SC_VERSION(1u)


#define SC_POLICY_BASE_MINOR_VERSION SC_POLICY_SET_SC_VERSION(0u)


#define SC_POLICY_SET_SC_VERSIONS(major, minor) ((major << SC_POLICY_SC_UINT_8_BITS) | minor)


#define SC_POLICY_BASE_VERSION SC_POLICY_SET_SC_VERSIONS(SC_POLICY_BASE_MAJOR_VERSION, SC_POLICY_BASE_MINOR_VERSION)


#define SC_POLICY_CHECK_BASE_VERSION(ver) (ver >= SC_POLICY_BASE_VERSION)
#define SC_POLICY_GET_MAJOR(ver) (ver >> SC_POLICY_SC_UINT_8_BITS)

#define SC_POLICY_CHECK_SUPPORT_VERSION(src_ver, now_ver) ((src_ver >> SC_POLICY_SC_UINT_8_BITS) <= (now_ver >> SC_POLICY_SC_UINT_8_BITS))
#define SC_POLICY_CHECK_MODULE_SUPPORT_VERSION(src_ver, module_ver) ((src_ver >> SC_POLICY_SC_UINT_8_BITS) >= (module_ver >> SC_POLICY_SC_UINT_8_BITS))

#define SC_POLICY_SET_NOW_VERSION(ver) ver


#define SC_POLICY_DEBUG
#define SC_POLICY_RELEASE
#undef SC_POLICY_DEBUG
#undef SC_POLICY_RELEASE


#define SC_POLICY_SPEED_CHARMFACE_ENGINE_NAME SPEED_CHARMFACE_ENGINE


#define SC_POLICY_SPEED_CHARM_PROJECT_NAME(format) SPEED_CHARM_ ## format


#define SC_POLICY_FINAL__


#define SC_POLICY_SC_PROJECT_NAME(format) sc ## format


#define sc_policy_si_strap static inline




#ifndef _SC_LOOSE_POLICY_H_
#define _SC_LOOSE_POLICY_H_

#if defined(_MSVC_VER_)


#define scfopen__(fp, f_path, f_mode) (fopen_s(&fp, f_path, f_mode) != 0)

#ifdef SC_LOOSE_POLICY_64_FILE


#define scftell__ _ftelli64

#define scfseek__ _fseeki64
#else

#define scftell__ ftell

#define scfseek__ fseek
#endif

#else


#define scfopen__(fp, f_path, f_mode) ((fp = fopen(f_path, f_mode)) == NULL)

#ifdef SC_LOOSE_POLICY_64_FILE


#define _FILE_OFFSET_BITS 64

#define scftell__ ftello

#define scftell__ fseeko
#else


#define scftell__ ftell

#define scfseek__ fseek
#endif

#endif


#define scfclose__ fclose

#define scfwrite__ fwrite

#define scfread__ fread


typedef sc_int64 scfsize_t____;

typedef scfsize_t____ scf_size_t;


#define sc_loose_policy_fopen(fp, f_path, f_mode) scfopen__(fp, f_path, f_mode)


#define sc_loose_policy_fclose(fp) (fp = (fp ? (scfclose__(fp), NULL) :  NULL))


#define sc_loose_policy_get_fpos(fp) scftell__(fp)


#define sc_loose_policy_fwrite(fp, buf, type, num) (scfwrite__(buf, sizeof(type), num, fp) == num)


#define sc_loose_policy_fread(fp, buf, type, num) (scfread__(buf, sizeof(type), num, fp) == num)


#define sc_loose_policy_seek(fp, off, opt) scfseek__(fp, off, opt)




#define scl_fopen sc_loose_policy_fopen


#define scl_close sc_loose_policy_fclose


#define scl_get_fpos sc_loose_policy_get_fpos


#define scl_fwrite sc_loose_policy_fwrite


#define scl_fread sc_loose_policy_fread


#define scl_fgoto sc_loose_policy_seek


#define scl_fgoto_e(fp) sc_loose_policy_seek(fp, 0, SEEK_END)

#ifdef _EXT_DEBUGGER_H_

typedef Ext_Debugger_Package Scl_Dp;

#define SC_LOOSE_POLICY_DEBUGGER(error_code, literal_log) set_debug_information(error_code, literal_log)


#define SC_LOOSE_POLICY_DP_PUT(dp) dp_puts_ln(dp, SC_POLICY_OUT_NORMAL)

#endif
#endif 


#endif

