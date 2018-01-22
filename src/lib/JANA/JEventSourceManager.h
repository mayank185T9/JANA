#ifndef JEventSourceManager_h
#define JEventSourceManager_h

#include <vector>
#include <deque>
#include <string>
#include <mutex>
#include <cstddef>

#include "JApplication.h"
#include "JEventSource.h"
#include "JEventSourceGenerator.h"

/**************************************************************** TYPE DECLARATIONS ****************************************************************/

class JEventSourceManager;

/**************************************************************** TYPE DEFINITIONS ****************************************************************/

class JEventSourceManager
{
	public:

		//STRUCTORS
		JEventSourceManager(JApplication* aApp);

		void AddEventSource(const std::string& source_name);
		void AddJEventSource(JEventSource *source);
		void AddJEventSourceGenerator(JEventSourceGenerator *source_generator);

		void GetJEventSources(std::vector<JEventSource*>& aSources) const;
		void GetJEventSourceGenerators(std::vector<JEventSourceGenerator*>& aGenerators) const;

		void OpenInitSources(void); //Call while single-threaded!!

		void ClearJEventSourceGenerators(void);
		void RemoveJEventSource(JEventSource *source);
		void RemoveJEventSourceGenerator(JEventSourceGenerator *source_generator);

		uint32_t GetNextEvent(void);
		void OpenNext(void);

	private:

		JEventSourceGenerator* GetUserEventSourceGenerator(void);
		JEventSourceGenerator* GetEventSourceGenerator(const std::string& source_name);

		void OpenSource(std::size_t islot, const std::string& source_name);

		JApplication* mApplication;
		std::size_t mMaxNumOpenFiles;

		std::vector<std::string> _source_names;
		std::deque<std::string> _source_names_unopened;

		std::vector<JEventSourceGenerator*> _eventSourceGenerators;
		std::vector<JEventSource*> _sources_active;
		std::vector<JEventSource*> _sources_exhausted;

		std::mutex _sources_exhausted_mutex;
		std::mutex _sources_open_mutex;
};

/**************************************************************** MEMBER FUNCTION DEFINITIONS ****************************************************************/

#endif
