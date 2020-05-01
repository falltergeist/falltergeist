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
                Dispatcher(const Dispatcher&) = delete;
                void operator=(const Dispatcher&) = delete;

                template<typename T>
                void scheduleEvent(EventTarget* target, std::unique_ptr<T> eventArg, Base::Delegate<T*> handlerArg);

                void processScheduledEvents();
                void blockEventHandlers(EventTarget* eventTarget);

            private:
                struct AbstractTask
                {
                    explicit AbstractTask(EventTarget* target);
                    virtual ~AbstractTask() = default;
                    virtual void perform() = 0;

                    EventTarget* target;
                };

                template <typename T>
                struct Task : AbstractTask
                {
                    Task(EventTarget* target, std::unique_ptr<T> event, Base::Delegate<T*> handler);
                    void perform() override;

                    std::unique_ptr<T> event;
                    Base::Delegate<T*> handler;
                };

                std::list<std::unique_ptr<AbstractTask>> _scheduledTasks, _tasksInProcess;
        };
    }
}
