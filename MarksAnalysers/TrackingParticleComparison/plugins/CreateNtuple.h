#ifndef MarksAnalysers_TrackingParticleComparison_CreateNtuple_h
#define MarksAnalysers_TrackingParticleComparison_CreateNtuple_h

#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>

//
// Forward declarations
//
namespace tpanalyserproto
{
	class Sample;
}

namespace tpanalyser
{
	/** @brief Analyser to look over collections of TrackingParticles.
	 *
	 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
	 * @date 10/Jun/2013
	 */
	class CreateNtuple : public edm::EDAnalyzer
	{
	public:
		explicit CreateNtuple( const edm::ParameterSet& config );
		virtual ~CreateNtuple();

		static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );
	private:
		virtual void beginJob();
		virtual void analyze( const edm::Event& event, const edm::EventSetup& setup );
		virtual void endJob();

//		virtual void beginRun( const edm::Run& run, const edm::EventSetup& setup );
//		virtual void endRun( const edm::Run& run, const edm::EventSetup& setup );
//		virtual void beginLuminosityBlock( const edm::LuminosityBlock& lumiBlock, const edm::EventSetup& setup );
//		virtual void endLuminosityBlock( const edm::LuminosityBlock& lumiBlock, const edm::EventSetup& setup );

		const edm::InputTag inputTag_;
		const std::string ntupleFilename_;
		std::unique_ptr<tpanalyserproto::Sample> pNtuple_;
	};

} // end of namespace tpanalyser

#endif
