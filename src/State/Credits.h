#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace UI
    {
        class TextArea;
    }
    namespace State
    {
        class Credits final : public State
        {
            public:
                Credits();
                ~Credits() override;

                void init() override;
                void think(const float &deltaTime) override;
                void handle(Event::Event* event) override;

                void onCreditsFinished();
                void onCreditsFadeDone(Event::State* event);
                void onStateActivate(Event::State* event) override;
            private:
                std::vector<UI::TextArea*> _lines;
                int* _linePositions = nullptr;
                float _timePassed = 0;
        };
    }
}
