/*
 * Copyright © 2017 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef GEM_CONTEXT_H
#define GEM_CONTEXT_H

#include <stdbool.h>
#include <stdint.h>

struct drm_i915_gem_context_param;

uint32_t gem_context_create(int fd);
int __gem_context_create(int fd, uint32_t *ctx_id);
void gem_context_destroy(int fd, uint32_t ctx_id);
int __gem_context_destroy(int fd, uint32_t ctx_id);

uint32_t gem_context_create_for_engine(int fd, unsigned int class, unsigned int inst);

int __gem_context_clone(int i915,
			uint32_t src, unsigned int share,
			unsigned int flags,
			uint32_t *out);
uint32_t gem_context_clone(int i915,
			   uint32_t src, unsigned int share,
			   unsigned int flags);
uint32_t gem_context_clone_with_engines(int i915, uint32_t src);
void gem_context_copy_engines(int src_fd, uint32_t src,
			      int dst_fd, uint32_t dst);

uint32_t gem_queue_create(int i915);
uint32_t gem_queue_clone_with_engines(int i915, uint32_t src);

bool gem_contexts_has_shared_gtt(int i915);
bool gem_has_queues(int i915);

bool gem_has_contexts(int fd);
void gem_require_contexts(int fd);
void gem_context_require_bannable(int fd);
void gem_context_require_param(int fd, uint64_t param);

bool gem_has_context_clone(int i915);

void gem_context_get_param(int fd, struct drm_i915_gem_context_param *p);
void gem_context_set_param(int fd, struct drm_i915_gem_context_param *p);
int __gem_context_set_param(int fd, struct drm_i915_gem_context_param *p);
int __gem_context_get_param(int fd, struct drm_i915_gem_context_param *p);

int __gem_context_set_priority(int fd, uint32_t ctx, int prio);
void gem_context_set_priority(int fd, uint32_t ctx, int prio);

int __gem_context_set_persistence(int i915, uint32_t ctx, bool state);
void gem_context_set_persistence(int i915, uint32_t ctx, bool state);

bool gem_context_has_engine(int fd, uint32_t ctx, uint64_t engine);

#endif /* GEM_CONTEXT_H */
