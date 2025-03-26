IF(UNIX)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-const-variable -Wno-switch -Wno-unknown-pragmas -Wno-enum-compare -Wno-unused-result  -Wno-tautological-compare -Wno-attributes -Wno-sign-compare -Wno-deprecated-declarations")
 IF(APPLE)
 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
ENDIF()	

  IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-but-set-variable -Wno-tautological-compare -Wno-unused-const-variable")
  ENDIF()
ELSE()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
ENDIF()




INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/source/common")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/source/i18n")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/source/io")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil")

IF(TRUE)
  ADD_LIBRARY(icudata STATIC ${CMAKE_CURRENT_SOURCE_DIR}/source/stubdata/stubdata.cpp)
ELSE()
  ADD_LIBRARY(icudata INTERFACE)
ENDIF()

add_definitions(
  -DUCONFIG_NO_LEGACY_CONVERSION=1
  -DUCONFIG_NO_IDNA=0
  -DUCONFIG_NO_TRANSLITERATION=1
  -DUCONFIG_NO_SERVICE=1
  -DUCONFIG_NO_REGULAR_EXPRESSIONS=1
  -DU_ENABLE_DYLOAD=0
  -DU_STATIC_IMPLEMENTATION=1
  -DU_HAVE_STD_STRING=0
  -DUCONFIG_NO_BREAK_ITERATION=0
)

SET(icuuc_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source/common/appendable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/bmpset.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/brkeng.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/brkiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/bytesinkutil.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/bytestream.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/bytestrie.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/bytestriebuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/bytestrieiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/caniter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/chariter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/charstr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/cmemory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/cstr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/cstring.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/cwchar.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/dictbe.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/dictionarydata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/dtintrv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/edits.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/errorcode.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/filteredbrk.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/filterednormalizer2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/icudataver.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/icuplug.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/listformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/loadednormalizer2impl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locavailable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locbased.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locdispnames.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locdspnm.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locid.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/loclikely.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locresdata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/locutil.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/messagepattern.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/normalizer2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/normalizer2impl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/normlzr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/parsepos.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/patternprops.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/pluralmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/propname.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/propsvec.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/punycode.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/putil.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbi.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbi_cache.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbidata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbinode.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbirb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbiscan.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbisetb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbistbl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/rbbitblb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/resbund.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/resbund_cnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/resource.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ruleiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/schriter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/serv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/servlk.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/servlkf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/servls.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/servnotf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/servrbf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/servslkf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/sharedobject.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/simpleformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/stringpiece.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/stringtriebuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uarrsort.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ubidi.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ubidi_props.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ubidiln.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ubiditransform.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ubidiwrt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ubrk.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucase.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucasemap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucasemap_titlecase_brkiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucat.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uchar.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucharstrie.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucharstriebuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucharstrieiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uchriter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucln_cmn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucmndata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv2022.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_bld.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_cb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_cnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_ct.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_err.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_ext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_io.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_lmb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_set.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_u16.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_u32.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_u7.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnv_u8.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvbocu.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvdisp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvhz.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvisci.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvlat1.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvmbcs.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvscsu.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucnvsel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucol_swp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ucurr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/udata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/udatamem.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/udataswp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uenum.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uhash.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uhash_us.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uidna.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uinit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uinvchar.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ulist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ulistformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uloc.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uloc_keytype.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uloc_tag.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/umapfile.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/umath.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/umutex.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unames.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unifiedcache.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unifilt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unifunct.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uniset.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uniset_closure.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uniset_props.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unisetspan.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unistr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unistr_case.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unistr_case_locale.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unistr_cnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unistr_props.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unistr_titlecase_brkiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unorm.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/unormcmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uobject.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uprops.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ures_cnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uresbund.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uresdata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/usc_impl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uscript.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uscript_props.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uset.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uset_props.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/usetiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ushape.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/usprep.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustack.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustr_cnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustr_titlecase_brkiter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustr_wcs.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustrcase.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustrcase_locale.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustrenum.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustrfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustring.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/ustrtrns.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utf_impl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/util.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/util_props.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utrace.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utrie.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utrie2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utrie2_builder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uts46.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/utypes.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uvector.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uvectr32.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/uvectr64.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/common/wintz.cpp
          )
ADD_LIBRARY(icuuc STATIC ${icuuc_SOURCE})

SOURCE_GROUP("src" FILES ${icuuc_SOURCE})

TARGET_COMPILE_DEFINITIONS(icuuc PRIVATE U_COMMON_IMPLEMENTATION)
TARGET_COMPILE_DEFINITIONS(icuuc PRIVATE UCONFIG_NO_CONVERSION=0)
TARGET_LINK_LIBRARIES(icuuc icudata)

SET(icui18n_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/affixpatternparser.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/alphaindex.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/anytrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/astro.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/basictz.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/bocsu.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/brktrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/buddhcal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/calendar.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/casetrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/cecal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/chnsecal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/choicfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/coleitr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/coll.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collation.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationbuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationcompare.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationdata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationdatabuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationdatareader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationdatawriter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationfastlatin.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationfastlatinbuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationfcd.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationkeys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationroot.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationrootelements.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationruleparser.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationsets.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationsettings.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationtailoring.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/collationweights.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/compactdecimalformat.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/coptccal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/cpdtrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csdetect.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csmatch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csr2022.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csrecog.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csrmbcs.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csrsbcs.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csrucode.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/csrutf8.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/curramt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/currfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/currpinf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/currunit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dangical.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/datefmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dayperiodrules.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dcfmtsym.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/decContext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/decNumber.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/decfmtst.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/decimalformatpattern.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/decimfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/decimfmtimpl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/digitaffix.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/digitaffixesandpadding.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/digitformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/digitgrouping.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/digitinterval.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/digitlst.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dtfmtsym.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dtitvfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dtitvinf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dtptngen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/dtrule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/esctrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ethpccal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/fmtable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/fmtable_cnv.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/format.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/fphdlimp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/fpositer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/funcrepl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/gender.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/gregocal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/gregoimp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/hebrwcal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/indiancal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/inputext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/islamcal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/japancal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/measfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/measunit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/measure.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/msgfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/name2uni.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/nfrs.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/nfrule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/nfsubs.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/nortrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/nounit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/nultrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_affixutils.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_compact.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_decimalquantity.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_decimfmtprops.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_fluent.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_formatimpl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_grouping.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_integerwidth.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_longnames.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_modifiers.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_notation.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_padding.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_patternmodifier.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_patternstring.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_rounding.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_scientific.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/number_stringbuilder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/numfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/numsys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/olsontz.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/persncal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/pluralaffix.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/plurfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/plurrule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/precision.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/quant.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/quantityformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbnf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbt_data.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbt_pars.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbt_rule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbt_set.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rbtz.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/regexcmp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/regeximp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/regexst.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/regextxt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/region.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/reldatefmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/reldtfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rematch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/remtrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/repattrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/rulebasedcollator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/scientificnumberformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/scriptset.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/search.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/selfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/sharedbreakiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/simpletz.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/smallintformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/smpdtfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/smpdtfst.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/sortkey.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/standardplural.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/strmatch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/strrepl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/stsearch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/taiwncal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/timezone.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/titletrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tmunit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tmutamt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tmutfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tolowtrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/toupptrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/translit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/transreg.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tridpars.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tzfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tzgnames.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tznames.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tznames_impl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tzrule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/tztrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucal.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucln_in.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucol.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucol_res.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucol_sit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucoleitr.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ucsdet.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/udat.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/udateintervalformat.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/udatpg.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ufieldpositer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uitercollationiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ulocdata.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/umsg.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/unesctrn.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uni2name.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/unum.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/unumsys.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/upluralrules.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uregex.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uregexc.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uregion.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/usearch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uspoof.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uspoof_build.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uspoof_conf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/uspoof_impl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/utf16collationiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/utf8collationiterator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/utmscale.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/utrans.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/valueformatter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/visibledigits.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/vtzone.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/vzone.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/windtfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/winnmfmt.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/wintzimpl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/zonemeta.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/zrule.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/i18n/ztrans.cpp
)

ADD_LIBRARY(icui18n STATIC ${icui18n_SOURCE})

SOURCE_GROUP("src" FILES ${icui18n_SOURCE})

TARGET_COMPILE_DEFINITIONS(icui18n PRIVATE U_I18N_IMPLEMENTATION)
TARGET_COMPILE_DEFINITIONS(icui18n PRIVATE UCONFIG_NO_CONVERSION=0)

TARGET_LINK_LIBRARIES(icui18n PUBLIC icuuc)

# TARGET_COMPILE_DEFINITIONS(icudata PUBLIC U_USING_ICU_NAMESPACE=0)
TARGET_COMPILE_DEFINITIONS(icui18n PUBLIC U_USING_ICU_NAMESPACE=0)
TARGET_COMPILE_DEFINITIONS(icuuc PUBLIC U_USING_ICU_NAMESPACE=0)

TARGET_COMPILE_DEFINITIONS(icui18n PRIVATE U_STATIC_IMPLEMENTATION)
TARGET_COMPILE_DEFINITIONS(icuuc PRIVATE U_STATIC_IMPLEMENTATION)

SET(icutools_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/collationinfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/denseranges.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/filestrm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/filetools.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/flagparser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/package.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_genc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_gencmn.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_icu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkgitems.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ppucd.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/swapimpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/toolutil.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ucbuf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ucln_tu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ucm.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ucmstate.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/unewdata.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/uoptions.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/uparse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/writesrc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/xmlparser.cpp
)

SET(icutools_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/collationinfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/denseranges.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/filestrm.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/filetools.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/flagparser.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/package.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_genc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_gencmn.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_icu.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/pkg_imp.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ppucd.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/swapimpl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/toolutil.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ucbuf.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/ucm.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/unewdata.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/uoptions.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/uparse.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/writesrc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/toolutil/xmlparser.h
)

ADD_LIBRARY(icutools STATIC ${icuuc_SOURCE} ${icui18n_SOURCE} ${icutools_HEADERS} ${icutools_SOURCE})

TARGET_COMPILE_DEFINITIONS(icutools PRIVATE U_TOOLUTIL_IMPLEMENTATION)
TARGET_COMPILE_DEFINITIONS(icutools PRIVATE U_COMMON_IMPLEMENTATION=1)
TARGET_COMPILE_DEFINITIONS(icutools PRIVATE U_I18N_IMPLEMENTATION=1)
TARGET_COMPILE_DEFINITIONS(icutools PRIVATE U_IO_IMPLEMENTATION=1)

SOURCE_GROUP("src" FILES ${icutools_SOURCE})
SOURCE_GROUP("include" FILES ${icutools_HEADERS})

SET(genrb_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/no-op.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/errmsg.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/genrb.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/parse.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/prscmnts.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/rbutil.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/read.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/reslist.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/rle.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/ustr.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/wrtjava.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genrb/wrtxml.cpp
)

SOURCE_GROUP("src" FILES ${genrb_SOURCE})

add_executable(genrb
              ${genrb_SOURCE}
)
TARGET_LINK_LIBRARIES(genrb icutools icudata)
 
add_executable(iculslocs
  ${CMAKE_CURRENT_SOURCE_DIR}/iculslocs.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/no-op.cc
)

TARGET_LINK_LIBRARIES(iculslocs icutools icudata)
 


add_executable(icupkg
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/icupkg/icupkg.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/no-op.cc
)

TARGET_LINK_LIBRARIES(icupkg icutools icudata)


add_executable(genccode
  ${CMAKE_CURRENT_SOURCE_DIR}/source/tools/genccode/genccode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/no-op.cc
)

TARGET_LINK_LIBRARIES(genccode icutools icudata)
 
IF(WIN32)

SET(genccode_OUT ${CMAKE_CURRENT_BINARY_DIR}/icudt60l_dat.obj)
SET(genccode_CMD
  ${CMAKE_CURRENT_BINARY_DIR}/bin/genccode.exe
  -o
  -d ${CMAKE_CURRENT_BINARY_DIR}/
  -n icudata
  -e icusmdt60l
  ${CMAKE_CURRENT_SOURCE_DIR}/source/data/in/icudt60l.dat
)

add_custom_command(OUTPUT ${genccode_OUT}
                   COMMAND ${genccode_CMD}
                   DEPENDS genccode
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Generating genccod libraries"
                   VERBATIM)
ELSE()

SET(genccode_OUT ${CMAKE_CURRENT_BINARY_DIR}/icudt60l_dat.c)
SET(genccode_CMD
  ${CMAKE_CURRENT_BINARY_DIR}/bin/genccode
  -d ${CMAKE_CURRENT_BINARY_DIR}/
  ${CMAKE_CURRENT_SOURCE_DIR}/source/data/in/icudt60l.dat
)

add_custom_command(OUTPUT ${genccode_OUT}
                   COMMAND ${genccode_CMD}
                   DEPENDS genccode
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Generating genccod libraries"
                   VERBATIM)
ENDIF()

IF(WIN32)
ADD_LIBRARY(icudt STATIC
  ${CMAKE_CURRENT_BINARY_DIR}/icudt60l_dat.obj
)

ELSE()
ADD_LIBRARY(icudt STATIC
  ${CMAKE_CURRENT_BINARY_DIR}/icudt60l_dat.c
)
ENDIF()

set(libs 
icudata 
icuuc 
icui18n 
icutools 
icudt 
)

set(bins 
genccode 
icupkg 
iculslocs 
genrb 
)

FOREACH(lb ${libs})
SET_TARGET_PROPERTIES(${lb} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(${lb} PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(${lb} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

  IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(${lb} PROPERTIES FOLDER external)
  ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
ENDFOREACH()

FOREACH(lb ${bins})
SET_TARGET_PROPERTIES(${lb} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
SET_TARGET_PROPERTIES(${lb} PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
  LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
SET_TARGET_PROPERTIES(${lb} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)
  IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
  SET_TARGET_PROPERTIES(${lb} PROPERTIES FOLDER external)
  ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
ENDFOREACH()
