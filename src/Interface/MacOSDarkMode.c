#include <stdio.h>
#include <stdlib.h>
#include "../main.h"

/*
 * If running on MacOS, returns 1 if darkmode is enabled, 0 otherwise.
 * If not running on MacOS, returns 0.
 * TODO: This function is a bit slow, see if we keep it for the final version 
  or not.
 *
 * Returns:
 *  int : 1 or 0 whether the darkmode is enabled or not
 */
int macOSDarkMode() {
  #if __APPLE__ // If macos
    
    int darkmode = 0;
    
    
    FILE *fp;
    char osascript_out[3];
    
    fp = popen("/usr/bin/osascript -e 'tell application \"System Events\" to get dark mode of appearance preferences as integer'", "r");
    if (fp != NULL) {
      fgets(osascript_out, 3, fp);
      
      char *extra;
      darkmode = strtol(osascript_out, &extra, 2);
    }
    
    pclose(fp);
    return darkmode;
    
  #else // If not macos
    return 0;
  #endif
}


/*
 * Provide a CSS for the interface.
 *
 * Parameters:
 *  char* : Path of the CSS file
 *
*/
void AddCSS(char* cssPath) {
  GtkCssProvider* provider = gtk_css_provider_new();
  GdkDisplay* display = gdk_display_get_default();
  GdkScreen* screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), cssPath ,NULL);
}