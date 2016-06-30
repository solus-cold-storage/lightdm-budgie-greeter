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

#include "greeter-window.h"
#include "util.h"

struct BudgieGreeterWindowPrivate {
        GtkWidget *top_panel;
};

/**
 * implemented down the bottom
 */
static void budgie_greeter_window_init(BudgieGreeterWindow *self);
static GtkWidget *budgie_greeter_window_create_panel(BudgieGreeterWindow *self);
static void budgie_greeter_window_init_css(void);

G_DEFINE_TYPE_WITH_PRIVATE(BudgieGreeterWindow, budgie_greeter_window, GTK_TYPE_WINDOW)

GtkWidget *budgie_greeter_window_new()
{
        return g_object_new(BUDGIE_TYPE_GREETER_WINDOW, NULL);
}

/**
 * Just hook up quit for now so we can hack-test the UI
 */
static gboolean budgie_greeter_window_delete(__budgie_unused__ GtkWidget *widget,
                                             __budgie_unused__ gpointer userdata)
{
        gtk_main_quit();
        return GDK_EVENT_STOP;
}

/**
 * Initialise our GreeterWindow correctly
 */
static void budgie_greeter_window_init(BudgieGreeterWindow *self)
{
        GtkStyleContext *context = NULL;
        GdkVisual *visual = NULL;
        GdkScreen *screen = NULL;
        GtkWidget *top_panel = NULL;
        GtkWidget *layout = NULL;

        self->priv = budgie_greeter_window_get_instance_private(self);
        g_signal_connect(G_OBJECT(self),
                         "delete-event",
                         G_CALLBACK(budgie_greeter_window_delete),
                         NULL);

        /* Set up an RGBA visual */
        screen = gdk_screen_get_default();
        visual = gdk_screen_get_rgba_visual(screen);
        if (visual) {
                gtk_widget_set_visual(GTK_WIDGET(self), visual);
        } else {
                fprintf(stderr, "Cannot set visual\n");
        }

        /* Load the CSS in */
        budgie_greeter_window_init_css();

        /* Some initial presentation cruft. */
        gtk_widget_set_size_request(GTK_WIDGET(self), 1024, 768);
        gtk_window_set_position(GTK_WINDOW(self), GTK_WIN_POS_CENTER);

        /* Get some styling in place */
        context = gtk_widget_get_style_context(GTK_WIDGET(self));
        gtk_style_context_add_class(context, "osd");

        /* Sort the layout .. out */
        layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(self), layout);

        /* Create the fake top panel */
        top_panel = budgie_greeter_window_create_panel(self);
        self->priv->top_panel = top_panel;
        gtk_box_pack_start(GTK_BOX(layout), top_panel, FALSE, FALSE, 0);
}

/**
 * Dispose of the current GreeterWindow
 */
static void budgie_greeter_window_dispose(GObject *object)
{
        /* No cleanups to be done yet */
        G_OBJECT_CLASS(budgie_greeter_window_parent_class)->dispose(object);
}

/**
 * Initialise the class members
 */
static void budgie_greeter_window_class_init(BudgieGreeterWindowClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);
        obj_class->dispose = budgie_greeter_window_dispose;
}

/**
 * Create a panel area to emulate BudgiePanel
 */
static GtkWidget *budgie_greeter_window_create_panel(BudgieGreeterWindow *self)
{
        GtkWidget *ebox = NULL;
        GtkWidget *layout = NULL;
        GtkWidget *shadow = NULL;
        GtkWidget *panel_area = NULL;
        GtkStyleContext *context = NULL;

        ebox = gtk_event_box_new();
        context = gtk_widget_get_style_context(ebox);
        gtk_style_context_add_class(context, "budgie-container");

        /* Fix layout */
        layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(ebox), layout);

        /* Create the ""panel"" */
        panel_area = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        context = gtk_widget_get_style_context(panel_area);
        gtk_style_context_add_class(context, "budgie-panel");

        gtk_box_pack_start(GTK_BOX(layout), panel_area, FALSE, FALSE, 0);
        gtk_widget_set_size_request(panel_area, -1, 35);

        /* Create the "shadow" */
        shadow = gtk_event_box_new();
        gtk_widget_set_size_request(shadow, -1, 5);
        context = gtk_widget_get_style_context(shadow);
        gtk_style_context_add_class(context, "shadow-block");

        gtk_box_pack_start(GTK_BOX(layout), shadow, FALSE, FALSE, 0);

        return ebox;
}

/**
 * Set up the theming by.. basically borrowing it from Budgie :P
 */
static void budgie_greeter_window_init_css()
{
        /* TODO: Check for the HC variant! */
        char *theme_name = budgie_form_theme_path("theme.css");
        GtkCssProvider *css_prov = NULL;
        GFile *file = NULL;
        GdkScreen *screen = NULL;

        file = g_file_new_for_uri(theme_name);
        if (!file) {
                fprintf(stderr, "Unable to locate theme\n");
                goto end;
        }

        css_prov = gtk_css_provider_new();
        if (!gtk_css_provider_load_from_file(css_prov, file, NULL)) {
                fprintf(stderr, "Failed to load theme %s\n", theme_name);
                goto end;
        }

        screen = gdk_screen_get_default();
        gtk_style_context_add_provider_for_screen(screen,
                                                  GTK_STYLE_PROVIDER(css_prov),
                                                  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

end:
        g_free(theme_name);
        if (file) {
                g_object_unref(file);
        }
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
