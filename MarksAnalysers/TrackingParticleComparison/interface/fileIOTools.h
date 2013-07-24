#ifndef MarksAnalysers_TrackingParticleComparison_fileIOTools_h
#define MarksAnalysers_TrackingParticleComparison_fileIOTools_h

#include <string>

//
// Forward declarations
//
namespace tpanalyserproto
{
	class Sample;
}

namespace tpanalyser
{
	/** @brief Save the provided Sample to the filename given.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 23/Jul/2013
	 */
	void saveSampleToFile( const tpanalyserproto::Sample& sample, const std::string& filename );

	/** @brief Loads a sample from the filename provided into the Sample provided.
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 23/Jul/2013
	 */
	void loadSampleFromFile( tpanalyserproto::Sample& sample, const std::string& filename );

} // end of namespace tpanalyser


#endif
