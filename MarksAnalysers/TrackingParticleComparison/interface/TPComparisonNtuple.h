#ifndef MarksAnalysers_TrackingParticleComparison_TPComparisonNtuple_h
#define MarksAnalysers_TrackingParticleComparison_TPComparisonNtuple_h

#include <string>
#include <memory>

namespace tpanalyser
{
	/** @brief Stores information about TrackingParticles to a file
	 *
	 * Only used for my personal debugging.
	 *
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 18/Jul/2013
	 */
	class TPComparisonNtuple
	{
	public:
		TPComparisonNtuple( const std::string filename="trackingParticleComparison.proto" );
		virtual ~TPComparisonNtuple();
		void newEvent();
		void setBeamSpot( float x, float y, float z );
		void setCurrentMatchedTrackCollection( size_t collectionNumber );
		void setCollectionName( const std::string& name );
		void addMatchedTrack( float dxyReconstructed, float dzReconstructed, float dxySimulated, float dzSimulated, float eta, float pt );
	private:
		std::unique_ptr<class TPComparisonNtuplePrivateMembers> pImple_;
	};

} // end of namespace tpanalyser


#endif
