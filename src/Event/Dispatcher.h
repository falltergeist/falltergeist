#include <list>
#include <memory>
#include "../Event/Event.h"
#include "../Event/EventTarget.h"

namespace Falltergeist
{
    namespace Event
    {
        class Dispatcher
        {
            public:
                Dispatcher() {}

                template<typename T>
                void scheduleEvent(EventTarget* target, std::unique_ptr<T> eventArg, Base::Delegate<T*> handlerArg);

                void processScheduledEvents();
                void blockEventHandlers(EventTarget* eventTarget);

            private:
                struct AbstractTask
                {
                    AbstractTask(EventTarget* target);
                    EventTarget* target;
                    virtual void perform() = 0;
                };

                template <typename T>
                struct Task : AbstractTask
                {
                    Task(EventTarget* target, std::unique_ptr<T> event, Base::Delegate<T*> handler);
                    void perform() override;

                    std::unique_ptr<T> event;
                    Base::Delegate<T*> handler;
                };


                Dispatcher(const Dispatcher&) = delete;
                void operator=(const Dispatcher&) = delete;

                std::list<std::unique_ptr<AbstractTask>> _scheduledTasks, _tasksInProcess;
        };
    }
}
