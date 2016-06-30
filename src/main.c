/*
 * This file is part of lightdm-budgie-greeter.
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * lightdm-budgie-greeter is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#include <budgie-desktop/theme.h>
#include <gtk/gtk.h>
#include <stdlib.h>

#include "greeter-window.h"

int main(int argc, char **argv)
{
        gtk_init(&argc, &argv);
        GtkWidget *window = NULL;

        /* Hack until we start using the theme library */
        budgie_please_link_me_libtool_i_have_great_themes();

        window = budgie_greeter_window_new();
        gtk_window_present(GTK_WINDOW(window));

        gtk_main();

        gtk_widget_destroy(window);

        return EXIT_SUCCESS;
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
