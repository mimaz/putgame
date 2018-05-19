/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>
#include <putgame/math>

#include "glass_pieces.hxx"

#include "glass_pane.hxx"
#include "object_manager.hxx"
#include "way_path.hxx"
#include "constants.hxx"
#include "camera.hxx"

namespace world
{
    namespace 
    {
        std::default_random_engine engine;
    }

    constexpr auto piece_size = 0.2f;

    glass_pieces::glass_pieces(common::context *ctx,
                               int frameid,
                               glm::vec3 color)
        : glass_pieces(ctx, frameid, color, tunnel_square_area)
    {}

    glass_pieces::glass_pieces(common::context *ctx,
                               int frameid,
                               glm::vec3 color,
                               glm::vec2 area)
        : glass_pieces(ctx, frameid, color, area, glm::mat4(1))
    {}

    glass_pieces::glass_pieces(common::context *ctx,
                               int frameid,
                               glm::vec3 color,
                               glm::vec2 area,
                               const glm::mat4 &transform)
        : visible_object(ctx, frameid)
        , color(color)
    {
        auto cam = get<camera>();
        auto cam_coord = cam->get_position();
        auto cam_direction = cam->get_direction();



        auto rand_angle = []() -> float {
            std::uniform_real_distribution<float> dist(0.02, 0.06);

            return dist(engine);
        };

        auto rand_axis = []() -> glm::vec3 {
            std::uniform_real_distribution<float> dist(0.25, 1.0);

            return glm::vec3(dist(engine), dist(engine), dist(engine));
        };

        auto rand_momentum = [=](const glm::mat4 &matrix) -> glm::mat4 {
            std::uniform_real_distribution<float> dist(0.5, 1.0);

            auto target = cam_coord + cam_direction * dist(engine);
            auto coord = math::coord3d(matrix);

            auto vector = (target - coord) * dist(engine);

            return glm::translate(vector / 400.0f);
        };



        auto xcount = static_cast<int>(area.x / piece_size);
        auto ycount = static_cast<int>(area.y / piece_size);

        auto xgap = area.x / (xcount - 1);
        auto ygap = area.y / (ycount - 1);
        auto zgap = (xgap + ygap) / 2;
        auto scale_vec = glm::vec3(xgap, ygap, zgap);

        auto base_matrix = transform * get_model();


        for (int y = 0; y < ycount; y++)
            for (int x = 0; x < xcount; x++)
            {
                auto yoff = y * ygap - area.y / 2;
                auto xoff = x * xgap - area.x / 2;

                auto off_vec = glm::vec3(xoff, yoff, 0.0f);
                auto matrix = base_matrix;
                auto rotate = glm::mat4(1);
                auto translate = glm::mat4(1);

                matrix = glm::translate(matrix, off_vec);
                matrix = glm::scale(matrix, scale_vec);

                rotate = glm::rotate(rotate, 
                                     rand_angle(), 
                                     rand_axis());

                translate = rand_momentum(matrix);

                matrixv.push_back(matrix);
                rotatev.push_back(rotate);
                translatev.push_back(translate);
                frameidv.push_back(frameid);
            }


        set_matrix(base_matrix);


        get<object_manager>()->add(this);
    }

    glass_pieces::~glass_pieces()
    {
        get<object_manager>()->remove(this);
    }

    void glass_pieces::update()
    {
        auto way = get<way_path>();
        auto range = 1;

        for (int i = 0; i < static_cast<int>(matrixv.size()); i++)
        {
            auto lastid = frameidv[i];

            frameidv[i] = way->updated_id(matrixv[i], frameidv[i]);
            matrixv[i] = translatev[i] * matrixv[i] * rotatev[i];

            if (frameidv[i] != lastid)
                continue;


            auto framemat = way->point(frameidv[i]);
            auto dist = math::sqdist(matrixv[i], framemat);

            if (dist > range)
            {
                matrixv[i] = matrixv.back();
                rotatev[i] = rotatev.back();
                translatev[i] = translatev.back();
                frameidv[i] = frameidv.back();

                matrixv.pop_back();
                rotatev.pop_back();
                translatev.pop_back();
                frameidv.pop_back();

                i--;
            }
        }

        assert(matrixv.size() == frameidv.size());
    }

    int glass_pieces::get_count() const
    {
        return static_cast<int>(matrixv.size());
    }

    glm::vec3 glass_pieces::get_color() const
    {
        return color;
    }

    const glm::mat4 *glass_pieces::get_matrices() const
    {
        return matrixv.data();
    }
}
