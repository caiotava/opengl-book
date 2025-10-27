#ifndef OPENGL_BOOK_LAYERSCENE_H
#define OPENGL_BOOK_LAYERSCENE_H

#include <memory>
#include "Scene.h"
#include <core/Layer.h>

namespace core {
    class LayerScene : public Layer {
    public:
        explicit LayerScene(std::unique_ptr<Scene> scene);
        virtual ~LayerScene();
        void OnUpdate(float ts) override;
        void OnRender() override;

        void SetScene(std::unique_ptr<Scene> scene);

    private:
        std::unique_ptr<Scene> m_scene;
    };
}


#endif //OPENGL_BOOK_LAYERSCENE_H
