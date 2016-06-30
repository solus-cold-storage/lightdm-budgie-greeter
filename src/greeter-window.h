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

#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _BudgieGreeterWindow BudgieGreeterWindow;
typedef struct _BudgieGreeterWindowClass BudgieGreeterWindowClass;
typedef struct BudgieGreeterWindowPrivate BudgieGreeterWindowPrivate;

#define BUDGIE_TYPE_GREETER_WINDOW (budgie_greeter_window_get_type())
#define BUDGIE_GREETER_WINDOW(o)                                                                   \
        (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_GREETER_WINDOW, BudgieGreeterWindow))
#define BUDGIE_IS_GREETER_WINDOW(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_GREETER_WINDOW))
#define BUDGIE_GREETER_WINDOW_CLASS(o)                                                             \
        (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_GREETER_WINDOW, BudgieGreeterWindowClass))
#define BUDGIE_IS_GREETER_WINDOW_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_GREETER_WINDOW))
#define BUDGIE_GREETER_WINDOW_GET_CLASS(o)                                                         \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_GREETER_WINDOW, BudgieGreeterWindowClass))

/**
 * BudgieGreeterWindowClass
 */
struct _BudgieGreeterWindowClass {
        GtkWindowClass parent_class;
        gpointer padding[4];
};

struct _BudgieGreeterWindow {
        GtkWindow parent_instance;
        BudgieGreeterWindowPrivate *priv;
};

GType budgie_greeter_window_get_type(void);

G_END_DECLS

/**
 * Construct a new BudgieGreeterWindow
 */
GtkWidget *budgie_greeter_window_new(void);
