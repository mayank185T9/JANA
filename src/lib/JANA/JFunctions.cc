#include "JFunctions.h"
#include "JEvent.h"
#include "JTask.h"
#include "JApplication.h"

std::shared_ptr<JTaskBase> JMakeAnalyzeEventTask(std::shared_ptr<JEvent>& aEvent, JApplication* aApplication)
{
	//Get processors
	std::vector<JEventProcessor*> sProcessors;
	aApplication->GetJEventProcessors(sProcessors);

	//Define function that will be executed by the task (running processors on the event)
	auto sRunProcessors = [sProcessors](std::shared_ptr<JEvent>& aEvent) -> void
	{
		for(auto sProcessor : sProcessors)
			sProcessor->Process(aEvent);
	};
	auto sPackagedTask = std::packaged_task<void(std::shared_ptr<JEvent>&)>(sRunProcessors);

	//Get the JTask, set it up, and return it
	auto sTask = aApplication->GetVoidTask(); //std::make_shared<JTask<void>>(aEvent, sPackagedTask);
	sTask->SetEvent(std::move(aEvent));
	sTask->SetTask(std::move(sPackagedTask));
	return std::static_pointer_cast<JTaskBase>(sTask);
}

std::string JGetLongestQueueName(JThreadManager* aThreadManager, JEventSourceManager* aEventSourceManager)
{
	//Check
}
