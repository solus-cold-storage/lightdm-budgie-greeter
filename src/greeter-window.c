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
static gboolean budgie_greeter_window_delete(GtkWidget *widget, gpointer userdata)
{
        gtk_main_quit();
        return GDK_EVENT_STOP;
}

/**
 * Initialise our GreeterWindow correctly
 */
static void budgie_greeter_window_init(BudgieGreeterWindow *self)
{
        self->priv = budgie_greeter_window_get_instance_private(self);
        g_signal_connect(G_OBJECT(self),
                         "delete-event",
                         G_CALLBACK(budgie_greeter_window_delete),
                         NULL);
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
