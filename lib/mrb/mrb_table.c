/* -*- c-basic-offset: 2 -*- */
/*
  Copyright(C) 2014 Brazil

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License version 2.1 as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "../grn_ctx_impl.h"

#ifdef GRN_WITH_MRUBY
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

#include "mrb_ctx.h"
#include "mrb_table.h"

static mrb_value
mrb_grn_table_is_locked(mrb_state *mrb, mrb_value self)
{
  grn_ctx *ctx = (grn_ctx *)mrb->ud;
  unsigned int is_locked;

  is_locked = grn_obj_is_locked(ctx, DATA_PTR(self));
  grn_mrb_ctx_check(mrb);

  return mrb_bool_value(is_locked != 0);
}

static mrb_value
mrb_grn_table_get_size(mrb_state *mrb, mrb_value self)
{
  grn_ctx *ctx = (grn_ctx *)mrb->ud;
  unsigned int size;

  size = grn_table_size(ctx, DATA_PTR(self));
  grn_mrb_ctx_check(mrb);

  return mrb_fixnum_value(size);
}

void
grn_mrb_table_init(grn_ctx *ctx)
{
  grn_mrb_data *data = &(ctx->impl->mrb);
  mrb_state *mrb = data->state;
  struct RClass *module = data->module;
  struct RClass *object_class = data->object_class;
  struct RClass *klass;

  klass = mrb_define_class_under(mrb, module, "Table", object_class);
  MRB_SET_INSTANCE_TT(klass, MRB_TT_DATA);

  mrb_define_method(mrb, klass, "locked?",
                    mrb_grn_table_is_locked, MRB_ARGS_NONE());

  mrb_define_method(mrb, klass, "size",
                    mrb_grn_table_get_size, MRB_ARGS_NONE());
}
#endif
