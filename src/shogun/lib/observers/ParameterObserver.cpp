/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Giovanni De Toni
 *
 */

#include "ParameterObserver.h"
#include <shogun/lib/RefCount.h>
#include <shogun/lib/observers/ObservedValueTemplated.h>
#include <shogun/lib/observers/ParameterObserver.h>
#include <shogun/util/converters.h>

using namespace shogun;

ParameterObserver::ParameterObserver()
    : m_observed_parameters(), m_subscription_id(-1)
{
	SG_ADD(
	    &m_subscription_id, "subscription_id",
	    "Id of the subscription to an object.");
	this->watch_method(
	    "num_observations", &ParameterObserver::get_num_observations);
}

ParameterObserver::ParameterObserver(
    std::vector<std::string>& parameters,
    std::vector<ParameterProperties>& properties)
    : ParameterObserver()
{
	m_observed_parameters = parameters;
	m_observed_properties = properties;
}

ParameterObserver::ParameterObserver(std::vector<std::string>& parameters)
    : ParameterObserver()
{
	m_observed_parameters = parameters;
}

ParameterObserver::ParameterObserver(
    std::vector<ParameterProperties>& properties)
    : ParameterObserver()
{
	m_observed_properties = properties;
}

ParameterObserver::ParameterObserver(
    const std::string& filename, std::vector<std::string>& parameters,
    std::vector<ParameterProperties>& properties)
    : ParameterObserver(parameters, properties)
{
}

ParameterObserver::~ParameterObserver()
{
}

bool ParameterObserver::filter(const std::string& param)
{
	// If there are no specified parameters, then watch everything
	if (m_observed_parameters.size() == 0)
		return true;

	auto res = std::find(
	    m_observed_parameters.begin(), m_observed_parameters.end(), param);

	return res != m_observed_parameters.end();
}

bool ParameterObserver::filter(const AnyParameterProperties& property)
{

	// If there are no specified parameters, then watch everything
	if (m_observed_properties.size() == 0)
		return true;

	bool res = false;
	for (auto p : m_observed_properties)
		res |= property.has_property(p);

	return res;
}

index_t ParameterObserver::get_num_observations() const
{
	return utils::safe_convert<index_t>(m_observations.size());
};
