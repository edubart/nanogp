#include "sample_common.h"

int frame = 0;

void draw_rects(ngp_context* ngp) {
    int width = ngp->viewport.w, height = ngp->viewport.h;
    int size = 64;
    int hsize = size / 2;
    float time = frame / 60.0f;
    float t = (1.0f+sinf(time))/2.0f;

    // left
    ngp_push_transform(ngp);
    ngp_translate(ngp, width*0.25f - hsize, height*0.5f - hsize);
    ngp_translate(ngp, 0.0f, 2*size*t - size);
    ngp_set_color(ngp, t, 0.3f, 1.0f-t, 1.0f);
    ngp_fill_rect(ngp, 0, 0, size, size);
    ngp_pop_transform(ngp);

    // middle
    ngp_push_transform(ngp);
    ngp_translate(ngp, width*0.5f - hsize, height*0.5f - hsize);
    ngp_rotate_at(ngp, time, hsize, hsize);
    ngp_set_color(ngp, t, 1.0f - t, 0.3f, 1.0f);
    ngp_fill_rect(ngp, 0, 0, size, size);
    ngp_pop_transform(ngp);

    // right
    ngp_push_transform(ngp);
    ngp_translate(ngp, width*0.75f - hsize, height*0.5f - hsize);
    ngp_scale_at(ngp, t + 0.25f, t + 0.5f, hsize, hsize);
    ngp_set_color(ngp, 0.3f, t, 1.0f - t, 1.0f);
    ngp_fill_rect(ngp, 0, 0, size, size);
    ngp_pop_transform(ngp);
}

void draw_points(ngp_context* ngp) {
    float time = frame / 60.0f;
    ngp_set_color(ngp, 1.0f, 1.0f, 1.0f, 1.0f);
    int width = ngp->viewport.w, height = ngp->viewport.h;
    for(int y=64;y<height-64;y+=8) {
        for(int x=64;x<width-64;x+=8) {
            ngp_point(ngp, x, y);
        }
    }
}

void render(ng_context* ngctx, ngp_context* ngp) {
    int width, height;
    ngctx_get_drawable_size(ngctx, &width, &height);
    ngp_set_clear_color(ngp, 0.05f, 0.05f, 0.05f, 1.0f);
    ngp_begin(ngp, width, height);
    int hw = width / 2;
    int hh = height / 2;

    // top left
    ngp_viewport(ngp, 0, 0, hw, hh);
    ngp_set_color(ngp, 0.1f, 0.1f, 0.1f, 1.0f);
    ngp_fill_rect(ngp, 0, 0, hw, hh);
    draw_rects(ngp);

    // top right
    ngp_viewport(ngp, hw, 0, hw, hh);
    ngp_scissor(ngp, 0, 0, hw, hh / 2);
    draw_rects(ngp);
    ngp_reset_scissor(ngp);

    // bottom left
    ngp_viewport(ngp, 0, hh, hw, hh);
    draw_points(ngp);

    // bottom right
    ngp_viewport(ngp, hw, hh, hw, hh);
    ngp_set_color(ngp, 0.1f, 0.1f, 0.1f, 1.0f);
    ngp_fill_rect(ngp, 0, 0, hw, hh);
    draw_points(ngp);

    ngp_end(ngp);
    ngctx_swap(ngctx);

    frame++;
}

int main() {
    return sample_app(render);
}
