/**** Language Constants ****************************************************/

QString parse_lang(char * ...);


#define S_ENTER_YOUR_NAME                                                  lang[   0 ].s
#define S_SCANNING_USER_FILE                                               lang[   1 ].s
#define S_ENTER_PASSWORD                                                   lang[   2 ].s
#define S_MORE                                                             lang[   3 ].s
#define S_YES                                                              lang[   4 ].s
#define S_NO                                                               lang[   5 ].s
#define S_PRESS_ENTER_TO_CONTINUE                                          lang[   6 ].s
#define S_EVENT_HAS_TO_RUN                                                 lang[   7 ].s
#define S_UPCOMING_EVENT                                                   lang[   8 ].s
#define S_CHECK_MAIL_PROMPT                                                lang[   9 ].s
#define S_ASK_YES_NO                                                       lang[  10 ].s
#define S_ASK_NO_YES                                                       lang[  11 ].s
#define S_ENTER_SYSTEM_PASSWORD                                            lang[  12 ].s
#define S_WRONG_PASSWORD                                                   lang[  13 ].s
#define S_ILLEGAL_NAME                                                     lang[  14 ].s
#define S_WRONG_NAME_FORMAT                                                lang[  15 ].s
#define S_ARE_YOU_A_NEW_USER(p1)                                parse_lang(lang[  16 ].s , (p1))
#define S_NO_ACCESS_ON_THIS_NODE                                           lang[  17 ].s
#define S_LEAVE_MESSAGE_TO_SYSOP                                           lang[  18 ].s
#define S_HANGING_UP                                                       lang[  19 ].s
#define S_LEVEL_EXPIRED                                                    lang[  20 ].s
#define S_LEVEL_WILL_EXPIRE(p1)                                 parse_lang(lang[  21 ].s , (p1))
#define S_LOCKED_OUT                                                       lang[  22 ].s
#define S_PRIVATE_SYSTEM                                                   lang[  23 ].s
#define S_NOT_FOR_NEW_USERS                                                lang[  24 ].s
#define S_ASK_ANSI                                                         lang[  25 ].s
#define S_ASK_AVATAR                                                       lang[  26 ].s
#define S_ASK_AVATAR_PLUS                                                  lang[  27 ].s
#define S_ASK_FSED                                                         lang[  28 ].s
#define S_ASK_CLS                                                          lang[  29 ].s
#define S_ASK_PAUSE                                                        lang[  30 ].s
#define S_ASK_SCREENLENGTH(p1)                                  parse_lang(lang[  31 ].s , (p1))
#define S_ASK_CITY                                                         lang[  32 ].s
#define S_ASK_STATE                                                        lang[  33 ].s
#define S_ASK_VOICE_PHONE                                                  lang[  34 ].s
#define S_ASK_DATA_PHONE                                                   lang[  35 ].s
#define S_ASK_BIRTHDATE(p1)                                     parse_lang(lang[  36 ].s , (p1))
#define S_ASK_ALIAS                                                        lang[  37 ].s
#define S_ALIAS_BEING_USED                                                 lang[  38 ].s
#define S_ASK_PASSWORD(p1,p2)                                   parse_lang(lang[  39 ].s , (p1) , (p2))
#define S_ILLEGAL_PASSWORD                                                 lang[  40 ].s
#define S_ASK_PASSWORD_AGAIN                                               lang[  41 ].s
#define S_ASK_EVERYTHING_CORRECT                                           lang[  42 ].s
#define S_WRITE_MESSAGE_TITLE(p1)                               parse_lang(lang[  43 ].s , (p1))
#define S_NOT_ALLOWED_TO_WRITE_IN_AREA                                     lang[  44 ].s
#define S_ASK_WRITE_MSG_USING_YOUR_ALIAS                                   lang[  45 ].s
#define S_ASK_WRITE_MSG_USING_AN_ALIAS                                     lang[  46 ].s
#define S_ENTER_ALIAS_TO_USE                                               lang[  47 ].s
#define S_ENTER_ALL_IF_TO_EVERYONE                                         lang[  48 ].s
#define S_WRITE_MSG_TO                                                     lang[  49 ].s
#define S_CONFIRM_WRITE_MESSAGE_TO(p1)                          parse_lang(lang[  50 ].s,(p1))
#define S_FUZZY_SEARCH_LIST_HEADER                                         lang[  51 ].s
#define S_FUZZY_SEARCH_LIST_FOOTER                                         lang[  52 ].s
#define S_USER_NOT_LOCATED                                                 lang[  53 ].s
#define S_ENTER_NETMAIL_ADDRESS_HEADER                                     lang[  54 ].s
#define S_ENTER_NETMAIL_ADDRESS                                            lang[  55 ].s
#define S_CONFIRM_NETMAIL_ADDRESS(p1,p2,p3)                     parse_lang(lang[  56 ].s , (p1) , (p2) , (p3))
#define S_NOT_ENOUGH_NETMAIL_CREDIT(p1)                         parse_lang(lang[  57 ].s , (p1))
#define S_ASK_SEND_CRASH                                                   lang[  58 ].s
#define S_ASK_ATTACH_FILE                                                  lang[  59 ].s
#define S_FILE_TO_ATTACH                                                   lang[  60 ].s
#define S_SHOW_MESSAGE_SUBJECT(p1)                              parse_lang(lang[  61 ].s , (p1))
#define S_ENTER_MESSAGE_SUBJECT                                            lang[  62 ].s
#define S_ASK_PRIVATE_MESSAGE                                              lang[  63 ].s
#define S_SAVING_MESSAGE                                                   lang[  64 ].s
#define S_SAVING_MESSAGE_ERROR                                             lang[  65 ].s
#define S_MESSAGE_ABORTED                                                  lang[  66 ].s
#define S_USER_REQUESTS_CHAT(p1,p2)                             parse_lang(lang[  67 ].s,(p1),(p2))
#define S_MULTILINE_CHAT_STARTED                                           lang[  68 ].s
#define S_MULTILINE_CHAT_ENDED                                             lang[  69 ].s
#define S_FATAL_ERROR                                                      lang[  70 ].s
#define S_ACCESS_DENIED                                                    lang[  71 ].s
#define S_THIS_MESSAGE_AREA_IS_LOCKED                                      lang[  72 ].s
#define S_THERE_ARE_X_MESSAGES_IN_THIS_AREA(p1)                 parse_lang(lang[  73 ].s,(p1))
#define S_THERE_ARE_NO_MESSAGES_IN_THIS_AREA                               lang[  74 ].s
#define S_READ_MESSAGES_ORDER_SELECTION                                    lang[  75 ].s
#define S_READMSG_FORWARD                                                  lang[  76 ].s
#define S_READMSG_REVERSE                                                  lang[  77 ].s
#define S_READMSG_ALL                                                      lang[  78 ].s
#define S_READMSG_NEW                                                      lang[  79 ].s
#define S_READMSG_SELECTED                                                 lang[  80 ].s
#define S_READMSG_SELECTED_SEARCH_FOR                                      lang[  81 ].s
#define S_READMSG_INDIVIDUAL                                               lang[  82 ].s
#define S_READMSG_MARKED                                                   lang[  83 ].s
#define S_READMSG_ALL_FORWARD_OR_REVERSE                                   lang[  84 ].s
#define S_READMSG_START_AT_MESSAGE                                         lang[  85 ].s
#define S_READMSG_SEARCHING_NEW_MESSAGES                                   lang[  86 ].s
#define S_READMSG_NO_NEW_MESSAGES_FOUND                                    lang[  87 ].s
#define S_READMSG_X_NEW_MESSAGES_FOUND(p1)                      parse_lang(lang[  88 ].s , (p1))
#define S_READMSG_NO_MESSAGES_FOUND                                        lang[  89 ].s
#define S_READMSG_WAIT_AFTER_EACH_MSG                                      lang[  90 ].s
#define S_PRESS_S_TO_STOP_OR_P_TO_PAUSE                                    lang[  91 ].s
#define S_READMSG_INDIV_ASK_MSGNUM                                         lang[  92 ].s
#define S_READMSG_INDIV_MSG_NOT_FOUND                                      lang[  93 ].s
#define S_ASK_DELETE_MSG                                                   lang[  94 ].s
#define S_MESSAGE_MARKED                                                   lang[  95 ].s
#define S_EXPORT_MESSAGE_TO_FILE                                           lang[  96 ].s
#define S_THERE_IS_NO_PREVIOUS_MSG                                         lang[  97 ].s
#define S_NO_ACCESS_TO_REPLIES                                             lang[  98 ].s
#define S_END_OF_MESSAGES                                                  lang[  99 ].s
#define S_QSCAN_MESSAGES_ORDER_SELECTION                                   lang[ 100 ].s
#define S_QSCAN_MSG_HEADER                                                 lang[ 101 ].s
#define S_QSCAN_MSG_DATALINE(p1,p2,p3,p4,p5)                    parse_lang(lang[ 102 ].s , (p1) , (p2) , (p3) , (p4) , (p5) )
#define S_SCAN_MESSAGES_ORDER_SELECTION                                    lang[ 103 ].s
#define S_SCAN_MESSAGES_SHOWMSG(p1,p2,p3,p4,p5)                 parse_lang(lang[ 104 ].s , (p1) , (p2) , (p3) , (p4) , (p5) )
#define S_SCAN_MESSAGES_PROMPT                                             lang[ 105 ].s
#define S_ENTER_MENU_PASSWORD                                              lang[ 106 ].s
#define S_DOWNLOAD_TITLE                                                   lang[ 107 ].s
#define S_DOWNLOAD_DELAY(p1)                                    parse_lang(lang[ 108 ].s , (p1))
#define S_DOWNLOAD_NOT_NOW                                                 lang[ 109 ].s
#define S_ENTER_FILES_TO_DOWNLOAD                                          lang[ 110 ].s
#define S_ENTER_DOWNLOAD_FILENAME(p1)                           parse_lang(lang[ 111 ].s , (p1))
#define S_SEARCHING_FILE_DATABASE                                          lang[ 112 ].s
#define S_NO_PERSONAL_FILES_FOUND                                          lang[ 113 ].s
#define S_DOWNLOAD_FILES_FOUND_HEADER                                      lang[ 114 ].s
#define S_DOWNLOAD_FILE_FOUND_ENTRY(p1,p2,p3)                   parse_lang(lang[ 115 ].s , (p1),(p2),(p3))
#define S_FILE_EXCEEDS_LIMIT(p1)                                parse_lang(lang[ 116 ].s , (p1))
#define S_UPLOAD_REQUIRED(p1)                                   parse_lang(lang[ 117 ].s , (p1))
#define S_FILE_FOUND_ACTION_PROMPT                                         lang[ 118 ].s
#define S_ACTION_DOWNLOAD                                                  lang[ 119 ].s
#define S_FREE_FILE                                                        lang[ 120 ].s
#define S_ACTION_FILE_SKIPPED                                              lang[ 121 ].s
#define S_ACTION_FILE_QUIT                                                 lang[ 122 ].s
#define S_NO_FILES_FOUND                                                   lang[ 123 ].s
#define S_X_FILES_SELECTED(p1,p2,p3)                            parse_lang(lang[ 124 ].s , (p1),(p2),(p3))
#define S_NOT_ENOUGH_TIME_LEFT_FOR_DOWNLOAD                                lang[ 125 ].s
#define S_START_DOWNLOAD_PROMPT                                            lang[ 126 ].s
#define S_DOWNLOAD_ACTION_GOODBYE                                          lang[ 127 ].s
#define S_ACTIVATING_PROTOCOL                                              lang[ 128 ].s
#define S_COPYING_FROM_CDROM(p1)                                parse_lang(lang[ 129 ].s , (p1))
#define S_ERROR_COPYING_FROM_CDROM                                         lang[ 130 ].s
#define S_X_FILES_DOWNLOADED_SUCCESSFULLY(p1,p2)                parse_lang(lang[ 131 ].s , (p1),(p2))
#define S_X_FILES_NOT_DOWNLOADED(p1)                            parse_lang(lang[ 132 ].s , (p1))
#define S_HANGUP_AFTER_DOWNLOAD_PROMPT                                     lang[ 133 ].s
#define S_MORE_TAG                                                         lang[ 134 ].s
#define S_ENTER_FILE_TAGS                                                  lang[ 135 ].s
#define S_X_FILES_TAGGED(p1)                                    parse_lang(lang[ 136 ].s , (p1))
#define S_FILELIST_PRESS_S_TO_STOP                                         lang[ 137 ].s
#define S_END_OF_FILE_LISTING                                              lang[ 138 ].s
#define S_KEYWORD_SEARCH_TITLE_AND_PROMPT                                  lang[ 139 ].s
#define S_SEARCHING_FOR_KEYWORD(p1)                             parse_lang(lang[ 140 ].s , (p1))
#define S_END_OF_FILE_SEARCH                                               lang[ 141 ].s
#define S_NEW_FILES_SEARCH_TITLE_AND_PROMPT(p1)                 parse_lang(lang[ 142 ].s  ,(p1))
#define S_SEARCHING_FOR_NEW_FILES(p1)                           parse_lang(lang[ 143 ].s  ,(p1))
#define S_FILENAME_SEARCH_TITLE_AND_PROMPT                                 lang[ 144 ].s
#define S_SEARCHING_FOR_FILENAME(p1)                            parse_lang(lang[ 145 ].s  ,(p1))
#define S_CHANGE_CITY_TITLE_AND_PROMPT(p1)                      parse_lang(lang[ 146 ].s  ,(p1))
#define S_CHANGE_VOICE_PHONE_TITLE_AND_PROMPT(p1)               parse_lang(lang[ 147 ].s  ,(p1))
#define S_CHANGE_DATA_PHONE_TITLE_AND_PROMPT(p1)                parse_lang(lang[ 148 ].s  ,(p1))
#define S_CHANGE_STATE_TITLE_AND_PROMPT(p1)                     parse_lang(lang[ 149 ].s  ,(p1))
#define S_CHANGE_ALIAS_TITLE_AND_PROMPT(p1)                     parse_lang(lang[ 150 ].s  ,(p1))
#define S_CHANGE_SCREENLENGTH_TITLE_AND_PROMPT(p1)              parse_lang(lang[ 151 ].s  ,(p1))
#define S_ANSI_ENABLED                                                     lang[ 152 ].s
#define S_ANSI_DISABLED                                                    lang[ 153 ].s
#define S_AVATAR_ENABLED                                                   lang[ 154 ].s
#define S_AVATAR_DISABLED                                                  lang[ 155 ].s
#define S_AVTPLUS_ENABLED                                                  lang[ 156 ].s
#define S_AVTPLUS_DISABLED                                                 lang[ 157 ].s
#define S_FSED_ENABLED                                                     lang[ 158 ].s
#define S_FSED_DISABLED                                                    lang[ 159 ].s
#define S_CLS_ENABLED                                                      lang[ 160 ].s
#define S_CLS_DISABLED                                                     lang[ 161 ].s
#define S_PAUSE_ENABLED                                                    lang[ 162 ].s
#define S_PAUSE_DISABLED                                                   lang[ 163 ].s
#define S_IBMCHARS_ENABLED                                                 lang[ 164 ].s
#define S_IBMCHARS_DISABLED                                                lang[ 165 ].s
#define S_HOTKEYS_ENABLED                                                  lang[ 166 ].s
#define S_HOTKEYS_DISABLED                                                 lang[ 167 ].s
#define S_RIP_ENABLED                                                      lang[ 168 ].s
#define S_RIP_DISABLED                                                     lang[ 169 ].s
#define S_ASK_HOTKEYS                                                      lang[ 170 ].s
#define S_ASK_IBMCHARS                                                     lang[ 171 ].s
#define S_ASK_RIP                                                          lang[ 172 ].s
#define S_ASK_RIP_FONT                                                     lang[ 173 ].s
#define S_LARGE_RIP_FONT_SELECTED                                          lang[ 174 ].s
#define S_SMALL_RIP_FONT_SELECTED                                          lang[ 175 ].s
#define S_CHANGE_PASSWORD_TITLE                                            lang[ 176 ].s
#define S_ENTER_NEW_PASSWORD(p1)                                parse_lang(lang[ 177 ].s  ,(p1))
#define S_PASSWORD_CHANGED_SUCCESSFULLY                                    lang[ 178 ].s
#define S_LIST_USERS_TITLE_AND_PROMPT                                      lang[ 179 ].s
#define S_END_OF_USER_LIST                                                 lang[ 180 ].s
#define S_UPLOAD_TITLE                                                     lang[ 181 ].s
#define S_NOT_ENOUGH_FREE_DISK_SPACE                                       lang[ 182 ].s
#define S_NO_UPLOAD_DUE_TO_EVENT                                           lang[ 183 ].s
#define S_FILE_TO_UPLOAD                                                   lang[ 184 ].s
#define S_UPLOAD_START_PROMPT                                              lang[ 185 ].s
#define S_READY_TO_UPLOAD_FILES                                            lang[ 186 ].s
#define S_NO_FILES_RECEIVED                                                lang[ 187 ].s
#define S_CHECKING_UPLOADS                                                 lang[ 188 ].s
#define S_FILE_RECEIVED(p1)                                     parse_lang(lang[ 189 ].s , (p1))
#define S_DUPLICATE_UPLOAD_REMOVED                                         lang[ 190 ].s
#define S_DUPLICATE_UPLOAD                                                 lang[ 191 ].s
#define S_X_FILES_UPLOADED(p1,p2)                               parse_lang(lang[ 192 ].s , (p1),(p2))
#define S_NO_FILES_UPLOADED                                                lang[ 193 ].s
#define S_PLEASE_ENTER_UPLOAD_DESCRIPTIONS                                 lang[ 194 ].s
#define S_ENTER_USERNAME_FOR_PERSONAL_FILE(p1)                  parse_lang(lang[ 195 ].s , (p1))
#define S_ENTER_DESCRIPTION_LINE_1(p1)                          parse_lang(lang[ 196 ].s , (p1))
#define S_ENTER_DESCRIPTION_LINE_X                                         lang[ 197 ].s
#define S_USER_LIST_HEADER                                                 lang[ 198 ].s
#define S_UNMARKED_ALL_MESSAGES                                            lang[ 199 ].s
#define S_PAGED_TOO_MANY_TIMES                                             lang[ 200 ].s
#define S_PAGING_NOT_ALLOWED_RIGHT_NOW                                     lang[ 201 ].s
#define S_ASK_CHAT_REASON                                                  lang[ 202 ].s
#define S_CHAT_REASON_TOO_SHORT(p1)                             parse_lang(lang[ 203 ].s , (p1))
#define S_SYSOP_NOT_RESPONDING                                             lang[ 204 ].s
#define S_MSGED_HEADER                                                     lang[ 205 ].s
#define S_MSGED_COMMAND_LIST                                               lang[ 206 ].s
#define S_MSGED_LIST                                                       lang[ 207 ].s
#define S_MSGED_SAVE                                                       lang[ 208 ].s
#define S_MSGED_ASK_ABORT                                                  lang[ 209 ].s
#define S_MSGED_CONTINUE                                                   lang[ 210 ].s
#define S_MSGED_EDIT_LINE(p1)                                   parse_lang(lang[ 211 ].s , (p1))
#define S_MSGED_DELETE_LINE                                                lang[ 212 ].s
#define S_MSGED_DELETE_FROM_LINE(p1)                            parse_lang(lang[ 213 ].s , (p1))
#define S_MSGED_DELETE_TO_LINE(p1,p2)                           parse_lang(lang[ 214 ].s , (p1),(p2))
#define S_MSGED_X_LINES_DELETED(p1)                             parse_lang(lang[ 215 ].s , (p1))
#define S_MSGED_INSERT_LINE(p1)                                 parse_lang(lang[ 216 ].s , (p1))
#define S_MSGED_REPLACE_TEXT(p1)                                parse_lang(lang[ 217 ].s , (p1))
#define S_MSGED_ENTER_TEXT_TO_REPLACE                                      lang[ 218 ].s
#define S_MSGED_TEXT_NOT_FOUND                                             lang[ 219 ].s
#define S_MSGED_REPLACE_BY                                                 lang[ 220 ].s
#define S_MSGED_LINE_NOW_READS                                             lang[ 221 ].s
#define S_VIEW_ARCHIVE_TITLE_AND_PROMPT                                    lang[ 222 ].s
#define S_ARCHIVE_FILE_NOT_FOUND                                           lang[ 223 ].s
#define S_ARCHIVE_HEADER_FILENAME                                          lang[ 224 ].s
#define S_ARCHIVE_HEADER_DATE                                              lang[ 225 ].s
#define S_ARCHIVE_HEADER_TIME                                              lang[ 226 ].s
#define S_ARCHIVE_HEADER_ORIGSIZE                                          lang[ 227 ].s
#define S_ARCHIVE_HEADER_COMPSIZE                                          lang[ 228 ].s
#define S_TIME_LIMIT_EXCEEDED                                              lang[ 229 ].s
#define S_TIME_LIMIT_WARNING(p1)                                parse_lang(lang[ 230 ].s , (p1))
#define S_INACTIVITY_TIMEOUT(p1)                                parse_lang(lang[ 231 ].s , (p1))
#define S_INACTIVITY_WARNING(p1)                                parse_lang(lang[ 232 ].s , (p1))
#define S_MCHAT_TITLE                                                      lang[ 233 ].s
#define S_MCHAT_ENTER_NODE_NUMBER                                          lang[ 234 ].s
#define S_MCHAT_CALLING_OTHER_NODE                                         lang[ 235 ].s
#define S_MCHAT_NODE_IS_NOT_AVAILABLE                                      lang[ 236 ].s
#define S_MCHAT_STARTED                                                    lang[ 237 ].s
#define S_MCHAT_OTHER_NODE_HUNG_UP                                         lang[ 238 ].s
#define S_SELECT_AREAS_TO_SCAN_TITLE                                       lang[ 239 ].s
#define S_SELECT_COMBINED_AREAS_TITLE                                      lang[ 240 ].s
#define S_SELECT_AREAS_TO_TOGGLE                                           lang[ 241 ].s
#define S_ENABLE_OR_DISABLE_ALL_AREAS                                      lang[ 242 ].s
#define S_ALL_AREAS_ENABLED                                                lang[ 243 ].s
#define S_ALL_AREAS_DISABLED                                               lang[ 244 ].s
#define S_EDIT_TAGGED_TITLE                                                lang[ 245 ].s
#define S_EDIT_TAGGED_PROMPT                                               lang[ 246 ].s
#define S_ALL_FILE_TAGS_CLEARED                                            lang[ 247 ].s
#define S_ENTER_FILE_TO_UNTAG                                              lang[ 248 ].s
#define S_MAIL_FOUND_TITLE                                                 lang[ 249 ].s
#define S_MAIL_FOUND_ACTION_PROMPT                                         lang[ 250 ].s
#define S_CHECKING_MAILBOX                                                 lang[ 251 ].s
#define S_MAILBOX_EMPTY                                                    lang[ 252 ].s
#define S_MESSAGES_HAVE_BEEN_MARKED                                        lang[ 253 ].s
#define S_CHECKING_FOR_PERSONAL_FILES                                      lang[ 254 ].s
#define S_PERSONAL_FILES_FOUND                                             lang[ 255 ].s
#define S_PERSONAL_FILE_FROM(p1)                                parse_lang(lang[ 256 ].s , (p1))
#define S_PROTOCOL_MENU_TITLE                                              lang[ 257 ].s
#define S_PROTOCOL_MENU_GOBACK                                             lang[ 258 ].s
#define S_PROTOCOL_MENU_PROMPT                                             lang[ 259 ].s
#define S_ENTER_MESSAGE_AREA_NUMBER                                        lang[ 260 ].s
#define S_PRESS_ENTER_TO_LIST                                              lang[ 261 ].s
#define S_SELECT_MESSAGE_AREA_TITLE                                        lang[ 262 ].s
#define S_UNKNOWN_MESSAGE_AREA                                             lang[ 263 ].s
#define S_ENTER_FILE_AREA_NUMBER                                           lang[ 264 ].s
#define S_SELECT_FILE_AREA_TITLE                                           lang[ 265 ].s
#define S_UNKNOWN_FILE_AREA                                                lang[ 266 ].s
#define S_ZONELIST_HEADER                                                  lang[ 267 ].s
#define S_NETLIST_HEADER(p1)                                    parse_lang(lang[ 268 ].s , (p1))
#define S_NODELIST_HEADER(p1)                                   parse_lang(lang[ 269 ].s , (p1))
#define S_NODE_NUMBER_NOT_FOUND                                            lang[ 270 ].s
#define S_ENTER_FILENAME_TO_DISPLAY                                        lang[ 271 ].s
#define S_REPLY_TO_MSG_USING_YOUR_ALIAS                                    lang[ 272 ].s
#define S_REPLY_TO_MSG_USING_AN_ALIAS                                      lang[ 273 ].s
#define S_DO_YOU_WANT_TO_CHANGE_THE_SUBJECT                                lang[ 274 ].s
#define S_QUOTING_MESSAGE                                                  lang[ 275 ].s
#define S_SHOW_GIF_INFO_TITLE_AND_PROMPT                                   lang[ 276 ].s
#define S_SHOW_GIF_FILENAME                                                lang[ 277 ].s
#define S_SHOW_GIF_RESOLUTION                                              lang[ 278 ].s
#define S_SHOW_GIF_COLORS                                                  lang[ 279 ].s
#define S_ENTER_BULLETIN                                                   lang[ 280 ].s
#define S_FILE_NOT_FOUND                                                   lang[ 281 ].s
#define S_SELECT_MSG_AREA_TO_MOVE_MESSAGE_TO                               lang[ 282 ].s
#define S_MOVING_MESSAGE                                                   lang[ 283 ].s
#define S_FORWARD_IN_SAME_AREA                                             lang[ 284 ].s
#define S_SELECT_MSG_AREA_TO_FORWARD_MESSAGE_IN                            lang[ 285 ].s
#define S_FORWARD_MESSAGE_TO                                               lang[ 286 ].s
#define S_FORWARDING_MESSAGE                                               lang[ 287 ].s
#define S_TIME_STATS_TITLE                                                 lang[ 288 ].s
#define S_STATS_TIME_ONLINE(p1)                                 parse_lang(lang[ 289 ].s , (p1))
#define S_STATS_TIME_LEFT(p1)                                   parse_lang(lang[ 290 ].s , (p1))
#define S_STATS_FREE_TIME(p1)                                   parse_lang(lang[ 291 ].s , (p1))
#define S_STATS_TIME_TODAY(p1)                                  parse_lang(lang[ 292 ].s , (p1))
#define S_STATS_DAILY_TIME_LIMIT(p1)                            parse_lang(lang[ 293 ].s , (p1))
#define S_STATS_DAILY_DL_LIMIT(p1)                              parse_lang(lang[ 294 ].s , (p1))
#define S_STATS_DOWNLOAD_LEFT(p1)                               parse_lang(lang[ 295 ].s , (p1))
#define S_STATS_KB_DOWNLOAD(p1)                                 parse_lang(lang[ 296 ].s , (p1))
#define S_STATS_KB_UPLOADED(p1)                                 parse_lang(lang[ 297 ].s , (p1))
#define S_STATS_KB_UPLOAD_NEEDED(p1)                            parse_lang(lang[ 298 ].s , (p1))
#define S_STATS_FREE_DOWNLOAD(p1)                               parse_lang(lang[ 299 ].s , (p1))
#define S_STATS_LAST_CALLED(p1,p2)                              parse_lang(lang[ 300 ].s , (p1),(p2))
#define S_STATS_TOTAL_CALLS(p1)                                 parse_lang(lang[ 301 ].s , (p1))
#define S_TOPS_TOP_CALLERS                                                 lang[ 302 ].s
#define S_TOPS_TOP_CALLERS_UNIT                                            lang[ 303 ].s
#define S_TOPS_TOP_DOWNLOADERS_KB                                          lang[ 304 ].s
#define S_TOPS_TOP_DOWNLOADERS_KB_UNIT                                     lang[ 305 ].s
#define S_TOPS_TOP_DOWNLOADERS_TIMES                                       lang[ 306 ].s
#define S_TOPS_TOP_DOWNLOADERS_TIMES_UNIT                                  lang[ 307 ].s
#define S_TOPS_TOP_UPLOADERS_KB                                            lang[ 308 ].s
#define S_TOPS_TOP_UPLOADERS_KB_UNIT                                       lang[ 309 ].s
#define S_TOPS_TOP_UPLOADERS_TIMES                                         lang[ 310 ].s
#define S_TOPS_TOP_UPLOADERS_TIMES_UNIT                                    lang[ 311 ].s
#define S_TOPS_TOP_MSGWRITERS                                              lang[ 312 ].s
#define S_TOPS_TOP_MSGWRITERS_UNIT                                         lang[ 313 ].s
#define S_TOPS_TOP_ONLINE                                                  lang[ 314 ].s
#define S_TOPS_TOP_ONLINE_UNIT                                             lang[ 315 ].s
#define S_SHOW_USERS_ONLINE_HEADER                                         lang[ 316 ].s
#define S_USER_ONLINE_STATUS_BROWSING                                      lang[ 317 ].s
#define S_USER_ONLINE_STATUS_CHATTING                                      lang[ 318 ].s
#define S_USER_ONLINE_STATUS_ONLINE                                        lang[ 319 ].s
#define S_USER_ONLINE_STATUS_INSHELL                                       lang[ 320 ].s
#define S_USER_ONLINE_STATUS_BUSY                                          lang[ 321 ].s
#define S_USER_ONLINE_NO_USER_ONLINE                                       lang[ 322 ].s
#define S_DIRECTORY_TO_SHOW                                                lang[ 323 ].s
#define S_ONE_MOMENT_PLEASE                    ((char *)replace_stringvars(lang[ 324 ].s))
#define S_LOADING                              ((char *)replace_stringvars(lang[ 325 ].s))
#define S_SYSOP_SHELLING                       ((char *)replace_stringvars(lang[ 326 ].s))
#define S_SYSOP_RETURNED_FROM_DOS              ((char *)replace_stringvars(lang[ 327 ].s))
#define S_SYSOP_CHAT_START                     ((char *)replace_stringvars(lang[ 328 ].s))
#define S_SYSOP_CHAT_ENDED                     ((char *)replace_stringvars(lang[ 329 ].s))
#define S_SELECT_LANGUAGE_TITLE                                            lang[ 330 ].s
#define S_SELECT_LANGUAGE                                                  lang[ 331 ].s
#define S_READING_LANGUAGE_FILE                                            lang[ 332 ].s
#define S_INVALID_ENTRY                                                    lang[ 333 ].s
#define S_ASK_FAX_PHONE                                                    lang[ 334 ].s
#define S_ASK_MAILING_ADDRESS                                              lang[ 335 ].s
#define S_ASK_SEX                                                          lang[ 336 ].s
#define S_SELECT_DATE_FORMAT_TITLE                                         lang[ 337 ].s
#define S_SELECT_DATE_FORMAT_PROMPT                                        lang[ 338 ].s
#define S_CHANGE_FAX_PHONE_TITLE_AND_PROMPT(p1)                 parse_lang(lang[ 339 ].s  ,(p1))
#define S_CHANGE_MAILING_ADDRESS_TITLE_AND_PROMPT(p1)           parse_lang(lang[ 340 ].s  ,(p1))
#define S_CHANGE_DATE_FORMAT_TITLE(p1)                          parse_lang(lang[ 341 ].s  ,(p1))
#define S_MALE                                                             lang[ 342 ].s
#define S_FEMALE                                                           lang[ 343 ].s
#define S_UNKNOWN                                                          lang[ 344 ].s
#define S_ASK_COUNTRY                                                      lang[ 345 ].s
#define S_CHANGE_COUNTRY_TITLE_AND_PROMPT(p1)                   parse_lang(lang[ 346 ].s  ,(p1))
#define S_END_OF_LIST_TAG                                                  lang[ 347 ].s
#define S_SELECT_FILE_AREA_GROUP_TITLE                                     lang[ 348 ].s
#define S_SELECT_MSG_AREA_GROUP_TITLE                                      lang[ 349 ].s
#define S_ENTER_GROUP_NUMBER                                               lang[ 350 ].s
#define S_UNKNOWN_GROUP                                                    lang[ 351 ].s
#define S_DOWNLOAD_NOW                                                     lang[ 352 ].s
#define S_SCANNING_UPLOADS                                                 lang[ 353 ].s
#define S_FOLLOWING_FILES_REJECTED                                         lang[ 354 ].s
#define S_MSGHEADER_MESSAGENUM(p1,p2)                           parse_lang(lang[ 355 ].s  ,(p1),(p2))
#define S_MSGHEADER_PRIVATE                                                lang[ 356 ].s
#define S_MSGHEADER_CRASH                                                  lang[ 357 ].s
#define S_MSGHEADER_KILL                                                   lang[ 358 ].s
#define S_MSGHEADER_FILE                                                   lang[ 359 ].s
#define S_MSGHEADER_SENT                                                   lang[ 360 ].s
#define S_MSGHEADER_FROM(p1,p2,p3)                              parse_lang(lang[ 361 ].s , (p1),(p2),(p3))
#define S_MSGHEADER_TO(p1)                                      parse_lang(lang[ 362 ].s , (p1))
#define S_MSGHEADER_RECEIVED                                               lang[ 363 ].s
#define S_MSGHEADER_RECEIVED_ON(p1,p2)                          parse_lang(lang[ 364 ].s  ,(p1),(p2))
#define S_MSGHEADER_SUBJECT(p1)                                 parse_lang(lang[ 365 ].s  ,(p1))
#define S_MSGHEADER_FILEATTACHED(p1)                            parse_lang(lang[ 366 ].s  ,(p1))
#define S_MSGPROMPT_NEXT                                                   lang[ 367 ].s
#define S_MSGPROMPT_PREV                                                   lang[ 368 ].s
#define S_MSGPROMPT_AGAIN                                                  lang[ 369 ].s
#define S_MSGPROMPT_STOP                                                   lang[ 370 ].s
#define S_MSGPROMPT_MARK                                                   lang[ 371 ].s
#define S_MSGPROMPT_REPLY                                                  lang[ 372 ].s
#define S_MSGPROMPT_UNREAD                                                 lang[ 373 ].s
#define S_MSGPROMPT_DEL                                                    lang[ 374 ].s
#define S_MSGPROMPT_ORIG                                                   lang[ 375 ].s
#define S_MSGPROMPT_SYSOPFUNC                                              lang[ 376 ].s
#define S_MSGHELP_TITLE                                                    lang[ 377 ].s
#define S_MSGHELP_NEXT                                                     lang[ 378 ].s
#define S_MSGHELP_PREV                                                     lang[ 379 ].s
#define S_MSGHELP_AGAIN                                                    lang[ 380 ].s
#define S_MSGHELP_STOP                                                     lang[ 381 ].s
#define S_MSGHELP_MARK                                                     lang[ 382 ].s
#define S_MSGHELP_REPLY                                                    lang[ 383 ].s
#define S_MSGHELP_DEL                                                      lang[ 384 ].s
#define S_MSGHELP_UNREAD                                                   lang[ 385 ].s
#define S_MSGHELP_PLUS                                                     lang[ 386 ].s
#define S_MSGHELP_MINUS                                                    lang[ 387 ].s
#define S_MSGHELP_ORIG                                                     lang[ 388 ].s
#define S_MSGHELP_FORWARD                                                  lang[ 389 ].s
#define S_MSGHELP_PRIVATE                                                  lang[ 390 ].s
#define S_MSGHELP_MOVE                                                     lang[ 391 ].s
#define S_MSGHELP_EXPORT                                                   lang[ 392 ].s
#define S_MSGHELP_NOTE                                                     lang[ 393 ].s
#define S_CHANGE_PROTOCOL_TITLE(p1)                             parse_lang(lang[ 394 ].s , (p1))
#define S_NO_DEFAULT_PROTOCOL                                              lang[ 395 ].s
#define S_PROTOCOL_SELECTED(p1)                                 parse_lang(lang[ 396 ].s , (p1))
#define S_ENTER_SELECTION_PASSWORD                                         lang[ 397 ].s
#define S_SYSTEM_GOING_DOWN                                                lang[ 398 ].s

#define K_MORE                                          lang[   3 ].hotkeys
#define K_ASK_YES_NO                                    lang[  10 ].hotkeys
#define K_ASK_NO_YES                                    lang[  11 ].hotkeys
#define K_READ_MESSAGES_ORDER_SELECTION                 lang[  75 ].hotkeys
#define K_READMSG_SELECTED                              lang[  80 ].hotkeys
#define K_READMSG_ALL_FORWARD_OR_REVERSE                lang[  84 ].hotkeys
#define K_QSCAN_MESSAGES_ORDER_SELECTION                lang[ 100 ].hotkeys
#define K_SCAN_MESSAGES_ORDER_SELECTION                 lang[ 103 ].hotkeys
#define K_SCAN_MESSAGES_PROMPT                          lang[ 105 ].hotkeys
#define K_FILE_FOUND_ACTION_PROMPT                      lang[ 118 ].hotkeys
#define K_START_DOWNLOAD_PROMPT                         lang[ 126 ].hotkeys
#define K_HANGUP_AFTER_DOWNLOAD_PROMPT                  lang[ 133 ].hotkeys
#define K_MORE_TAG                                      lang[ 134 ].hotkeys
#define K_UPLOAD_START_PROMPT                           lang[ 185 ].hotkeys
#define K_MSGED_COMMAND_LIST                            lang[ 206 ].hotkeys
#define K_ENABLE_OR_DISABLE_ALL_AREAS                   lang[ 242 ].hotkeys
#define K_EDIT_TAGGED_PROMPT                            lang[ 246 ].hotkeys
#define K_MAIL_FOUND_ACTION_PROMPT                      lang[ 250 ].hotkeys
#define K_ASK_SEX                                       lang[ 336 ].hotkeys
#define K_END_OF_LIST_TAG                               lang[ 347 ].hotkeys
#define K_MSGPROMPT_NEXT                                lang[ 367 ].hotkeys
#define K_MSGPROMPT_PREV                                lang[ 368 ].hotkeys
#define K_MSGPROMPT_AGAIN                               lang[ 369 ].hotkeys
#define K_MSGPROMPT_STOP                                lang[ 370 ].hotkeys
#define K_MSGPROMPT_MARK                                lang[ 371 ].hotkeys
#define K_MSGPROMPT_REPLY                               lang[ 372 ].hotkeys
#define K_MSGPROMPT_UNREAD                              lang[ 373 ].hotkeys
#define K_MSGPROMPT_DEL                                 lang[ 374 ].hotkeys
#define K_MSGPROMPT_ORIG                                lang[ 375 ].hotkeys
#define K_MSGPROMPT_SYSOPFUNC                           lang[ 376 ].hotkeys
