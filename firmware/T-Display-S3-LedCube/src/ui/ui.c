// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.2.3
// LVGL version: 8.2.0
// Project name: LedCubeDisplay

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
void ui_event_backButton(lv_event_t * e);
lv_obj_t * ui_backButton;
lv_obj_t * ui_backImage;
void ui_event_playButton(lv_event_t * e);
lv_obj_t * ui_playButton;
lv_obj_t * ui_playImage;
lv_obj_t * ui_aninmationText;
void ui_event_forwardButton(lv_event_t * e);
lv_obj_t * ui_forwardButton;
lv_obj_t * ui_forwardImage;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_backButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        backButtonPressed(e);
    }
}
void ui_event_playButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_image_set_property(ui_playImage, _UI_IMAGE_PROPERTY_IMAGE, & ui_img_pause_png);
        _ui_basic_set_property(ui_playImage, _UI_BASIC_PROPERTY_POSITION_X,  0);
        playButtonPressed(e);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        _ui_image_set_property(ui_playImage, _UI_IMAGE_PROPERTY_IMAGE, & ui_img_play_png);
        _ui_basic_set_property(ui_playImage, _UI_BASIC_PROPERTY_POSITION_X,  2);
        pauseButtonPressed(e);
    }
}
void ui_event_forwardButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        forwardButtonPressed(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_backButton = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_backButton, 50);
    lv_obj_set_height(ui_backButton, 50);
    lv_obj_set_x(ui_backButton, 35);
    lv_obj_set_y(ui_backButton, -20);
    lv_obj_set_align(ui_backButton, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_backButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_backButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_backButton, lv_color_hex(0x474655), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_backButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_backImage = lv_img_create(ui_backButton);
    lv_img_set_src(ui_backImage, &ui_img_backward_png);
    lv_obj_set_width(ui_backImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_backImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_backImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_backImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_backImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_playButton = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_playButton, 70);
    lv_obj_set_height(ui_playButton, 70);
    lv_obj_set_x(ui_playButton, 0);
    lv_obj_set_y(ui_playButton, -10);
    lv_obj_set_align(ui_playButton, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_playButton, LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_playButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_playButton, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_playButton, lv_color_hex(0x474655), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_playButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_playButton, lv_color_hex(0x474655), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_playButton, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_playImage = lv_img_create(ui_playButton);
    lv_img_set_src(ui_playImage, &ui_img_pause_png);
    lv_obj_set_width(ui_playImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_playImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_playImage, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_playImage, LV_STATE_CHECKED);       /// States
    lv_obj_add_flag(ui_playImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_playImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_playImage, 400);

    ui_aninmationText = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_aninmationText, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_aninmationText, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_aninmationText, 0);
    lv_obj_set_y(ui_aninmationText, 31);
    lv_obj_set_align(ui_aninmationText, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_aninmationText, "Animation");
    lv_obj_set_style_text_font(ui_aninmationText, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forwardButton = lv_btn_create(ui_Screen1);
    lv_obj_set_width(ui_forwardButton, 50);
    lv_obj_set_height(ui_forwardButton, 50);
    lv_obj_set_x(ui_forwardButton, -35);
    lv_obj_set_y(ui_forwardButton, -20);
    lv_obj_set_align(ui_forwardButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_forwardButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_forwardButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_forwardButton, lv_color_hex(0x474655), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_forwardButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_forwardImage = lv_img_create(ui_forwardButton);
    lv_img_set_src(ui_forwardImage, &ui_img_forward_png);
    lv_obj_set_width(ui_forwardImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_forwardImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_forwardImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_forwardImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_forwardImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_backButton, ui_event_backButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_playButton, ui_event_playButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_forwardButton, ui_event_forwardButton, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}