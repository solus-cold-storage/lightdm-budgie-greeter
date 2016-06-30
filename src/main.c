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

int main(int argc, char **argv)
{
        gtk_init(&argc, &argv);

        /* Hack until we start using the theme library */
        budgie_please_link_me_libtool_i_have_great_themes();

        return EXIT_SUCCESS;
}
