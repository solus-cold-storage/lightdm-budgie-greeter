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

#include "greeter-window.h"
#include "util.h"

struct BudgieGreeterWindowPrivate {
        int x;
};

/**
 * implemented down the bottom
 */
static void budgie_greeter_window_init(BudgieGreeterWindow *self);

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

        /* Some initial presentation cruft. */
        gtk_widget_set_size_request(GTK_WIDGET(self), 1024, 768);
        gtk_window_set_position(GTK_WINDOW(self), GTK_WIN_POS_CENTER);

        /* Get some styling in place */
        context = gtk_widget_get_style_context(GTK_WIDGET(self));
        gtk_style_context_add_class(context, "osd");
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
