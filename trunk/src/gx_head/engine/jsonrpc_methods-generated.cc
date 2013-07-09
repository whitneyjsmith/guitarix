/* generated by make_jsonrpc_methods.py */

/* ANSI-C code produced by gperf version 3.0.3 */
/* Command-line: gperf  */
/* Computed positions: -k'1,6,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

/* maximum key range = 153, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
      156, 156, 156, 156, 156,  70, 156,  30,  20,  60,
       25,  10, 156,  10,   0,  55,  30,  15,  25,  50,
       10,  15,  55,   0,   0,   0,   0, 105,   5,  20,
      156,  10, 156, 156, 156, 156, 156, 156
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct CmdConnection::methodnames *
in_word_set (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 76,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 27,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 155
    };

  static const struct CmdConnection::methodnames wordlist[] =
    {
      {""}, {""}, {""},
      {"set", RPNM_set},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"switch_tuner", RPNM_switch_tuner},
      {"get", RPCM_get},
      {""}, {""}, {""}, {""}, {""},
      {"setpreset", RPNM_setpreset},
      {""}, {""}, {""},
      {"rename_preset", RPCM_rename_preset},
      {"reorder_preset", RPNM_reorder_preset},
      {"banks", RPCM_banks},
      {"remove_rack_unit", RPNM_remove_rack_unit},
      {"set_oscilloscope_mul_buffer", RPNM_set_oscilloscope_mul_buffer},
      {""},
      {"list", RPCM_list},
      {"getversion", RPCM_getversion},
      {""},
      {"bank_reorder", RPNM_bank_reorder},
      {"shutdown", RPNM_shutdown},
      {""},
      {"request_midi_value_update", RPNM_request_midi_value_update},
      {"rename_bank", RPCM_rename_bank},
      {"get_oscilloscope_mul_buffer", RPCM_get_oscilloscope_mul_buffer},
      {""},
      {"bank_save", RPNM_bank_save},
      {"save_ladspalist", RPNM_save_ladspalist},
      {"bank_remove", RPCM_bank_remove},
      {""},
      {"bank_set_flag", RPNM_bank_set_flag},
      {"reload_impresp_list", RPNM_reload_impresp_list},
      {""},
      {"get_oscilloscope_info", RPCM_get_oscilloscope_info},
      {"bank_get_contents", RPCM_bank_get_contents},
      {"setstate", RPNM_setstate},
      {""}, {""},
      {"listen", RPNM_listen},
      {""},
      {"get_parameter", RPCM_get_parameter},
      {""},
      {"read_audio", RPCM_read_audio},
      {""},
      {"bank_get_filename", RPCM_bank_get_filename},
      {"getstate", RPCM_getstate},
      {"get_rack_unit_order", RPCM_get_rack_unit_order},
      {"get_jack_load_status", RPCM_get_jack_load_status},
      {""},
      {"presets", RPCM_presets},
      {"get_bank", RPCM_get_bank},
      {""},
      {"load_ladspalist", RPCM_load_ladspalist},
      {"save_preset", RPNM_save_preset},
      {""}, {""},
      {"midi_size", RPCM_midi_size},
      {"pf_insert_after", RPNM_pf_insert_after},
      {"insert_rack_unit", RPNM_insert_rack_unit},
      {"save_current", RPNM_save_current},
      {""},
      {"convert_preset", RPCM_convert_preset},
      {"pluginlist", RPCM_pluginlist},
      {""},
      {"pf_save", RPNM_pf_save},
      {"parameterlist", RPCM_parameterlist},
      {""},
      {"midi_set_config_mode", RPNM_midi_set_config_mode},
      {"pf_insert_before", RPNM_pf_insert_before},
      {"ladspaloader_update_plugins", RPCM_ladspaloader_update_plugins},
      {""},
      {"get_max_input_level", RPCM_get_max_input_level},
      {"get_max_output_level", RPCM_get_max_output_level},
      {""},
      {"plugin_preset_list_set", RPNM_plugin_preset_list_set},
      {""},
      {"desc", RPCM_desc},
      {"midi_get_config_mode", RPCM_midi_get_config_mode},
      {""},
      {"erase_preset", RPNM_erase_preset},
      {""},
      {"bank_insert_content", RPCM_bank_insert_content},
      {"midi_deleteParameter", RPNM_midi_deleteParameter},
      {""},
      {"load_impresp_dirs", RPCM_load_impresp_dirs},
      {"plugin_preset_list_save", RPNM_plugin_preset_list_save},
      {"midi_set_current_control", RPNM_midi_set_current_control},
      {"plugin_preset_list_remove", RPNM_plugin_preset_list_remove},
      {"tuner_switcher_toggle", RPNM_tuner_switcher_toggle},
      {"tuner_used_for_display", RPNM_tuner_used_for_display},
      {"tuner_switcher_activate", RPNM_tuner_switcher_activate},
      {""},
      {"tuner_switcher_deactivate", RPNM_tuner_switcher_deactivate},
      {""}, {""},
      {"bank_check_reparse", RPCM_bank_check_reparse},
      {""},
      {"bank_insert_new", RPCM_bank_insert_new},
      {""}, {""},
      {"plugin_preset_list_load", RPCM_plugin_preset_list_load},
      {"queryunit", RPCM_queryunit},
      {""}, {""}, {""},
      {"midi_modifyCurrent", RPNM_midi_modifyCurrent},
      {""}, {""}, {""}, {""},
      {"unlisten", RPNM_unlisten},
      {""}, {""}, {""}, {""},
      {"jack_cpu_load", RPCM_jack_cpu_load},
      {"get_tuner_freq", RPCM_get_tuner_freq},
      {""}, {""}, {""}, {""},
      {"plugin_load_ui", RPCM_plugin_load_ui},
      {"get_tuning", RPCM_get_tuning},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"get_midi_controller_map", RPCM_get_midi_controller_map},
      {"pf_append", RPNM_pf_append},
      {""}, {""}, {""}, {""}, {""},
      {"get_tuner_switcher_active", RPCM_get_tuner_switcher_active},
      {""}, {""}, {""}, {""},
      {"clear_oscilloscope_buffer", RPNM_clear_oscilloscope_buffer}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}


const jsonrpc_method_def jsonrpc_method_list[] = {
	{ "getversion", true },
	{ "shutdown", false },
	{ "listen", false },
	{ "unlisten", false },
	{ "getstate", true },
	{ "setstate", false },
	{ "jack_cpu_load", true },
	{ "get_jack_load_status", true },
	{ "get", true },
	{ "set", false },
	{ "parameterlist", true },
	{ "get_parameter", true },
	{ "desc", true },
	{ "list", true },
	{ "banks", true },
	{ "setpreset", false },
	{ "bank_insert_content", true },
	{ "bank_insert_new", true },
	{ "get_bank", true },
	{ "rename_bank", true },
	{ "bank_remove", true },
	{ "bank_get_contents", true },
	{ "bank_reorder", false },
	{ "bank_check_reparse", true },
	{ "bank_get_filename", true },
	{ "bank_set_flag", false },
	{ "convert_preset", true },
	{ "bank_save", false },
	{ "pf_save", false },
	{ "save_current", false },
	{ "save_preset", false },
	{ "presets", true },
	{ "rename_preset", true },
	{ "reorder_preset", false },
	{ "erase_preset", false },
	{ "pf_append", false },
	{ "pf_insert_before", false },
	{ "pf_insert_after", false },
	{ "plugin_preset_list_load", true },
	{ "plugin_preset_list_set", false },
	{ "plugin_preset_list_save", false },
	{ "plugin_preset_list_remove", false },
	{ "pluginlist", true },
	{ "plugin_load_ui", true },
	{ "get_rack_unit_order", true },
	{ "insert_rack_unit", false },
	{ "remove_rack_unit", false },
	{ "queryunit", true },
	{ "get_midi_controller_map", true },
	{ "midi_size", true },
	{ "midi_deleteParameter", false },
	{ "midi_modifyCurrent", false },
	{ "midi_get_config_mode", true },
	{ "midi_set_config_mode", false },
	{ "midi_set_current_control", false },
	{ "request_midi_value_update", false },
	{ "get_tuning", true },
	{ "get_tuner_freq", true },
	{ "switch_tuner", false },
	{ "tuner_used_for_display", false },
	{ "get_max_input_level", true },
	{ "get_max_output_level", true },
	{ "set_oscilloscope_mul_buffer", false },
	{ "get_oscilloscope_mul_buffer", true },
	{ "clear_oscilloscope_buffer", false },
	{ "get_oscilloscope_info", true },
	{ "reload_impresp_list", false },
	{ "load_impresp_dirs", true },
	{ "read_audio", true },
	{ "load_ladspalist", true },
	{ "save_ladspalist", false },
	{ "ladspaloader_update_plugins", true },
	{ "get_tuner_switcher_active", true },
	{ "tuner_switcher_activate", false },
	{ "tuner_switcher_deactivate", false },
	{ "tuner_switcher_toggle", false },
};
