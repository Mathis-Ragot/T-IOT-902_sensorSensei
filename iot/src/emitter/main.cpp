#include <vector>

int setup() {
    return 0;
}

int loop() {
    return 0;
}

namespace Domain {

    class ISensor {
        virtual int getValue() = 0;
    };

    class HumiditySensor : public ISensor {
        int getValue() {
            return 0;
        }
    };

    class TemperatureSensor : public ISensor {
        int getValue() {
            return 0;
        }
    };
}

namespace Event {
    class IEvent {
    };

    class HumidityEvent : public IEvent {

    };

    class TemperatureEvent : public IEvent {

    };
}

namespace Application {
    class IObserver {
        virtual void onEvent(Event::IEvent* event) = 0;
    };

    class SensorObserver : public IObserver {
        void onEvent(Event::IEvent* event) {

        }
    };
};

class EventBus {
  std::vector<Domain::ISensor*> sensors;
};

int main() {
    EventBus bus;
    Domain::HumiditySensor humiditySensor;
}