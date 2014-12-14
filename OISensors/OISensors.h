/* Created and copyrighted by Zachary J. Fields. All rights reserved. */

#ifndef OI_SENSORS_H
#define OI_SENSORS_H

#include <cstdint>
#include <functional>

#include "../OIDefines.h"

//TODO: Consider method to return multiple sensor values (std::tuple<uint_opt8_t packet_id_, uint16_t value_, bool signed_>)

namespace roomba {
namespace series500 {
namespace oi {

/// \brief Data type loaded by sensor methods
/// \details Sensor data is returned as a byte array
/// with checksum. This type reflects the data
/// representation of the returned sensor data,
/// as it strikes the balance between usability,
/// size and speed optimization.
/// see OICommand::sensors
/// see OICommand::queryList
/// see OICommand::stream
/// see OICommand::pauseResumeStream
namespace sensors {
	/// \brief Return codes
	enum ReturnCode : int_opt8_t {
		INVALID_CHECKSUM = -101,
		SERIAL_TRANSFER_FAILURE = -100,
		INVALID_PARAMETER = -10,
		NO_DATA_AVAILABLE = -4,
		FAILURE_TO_SYNC = -3,
		INVALID_MODE_FOR_REQUESTED_OPERATION = -2,
		SUCCESS = 0,
	};
	
	/// \brief Function to initialize sensor
	/// \details Enables the sensor functionality by setting
	/// the pointer to the serial read function; enabling
	/// serial communication.
	/// \param fnSerialRead_ A multi-byte read serial read function
	/// \return SUCCESS
	/// \see end
	ReturnCode
	begin (
		std::function<size_t(uint_opt8_t * const, const size_t)> fnSerialRead_
	);
	
	/// \brief Release resources tied to sensors
	/// \details Restores internal variables to a state ready for
	/// the next call to begin().
	/// \return SUCCESS
	/// \see begin
	ReturnCode
	end (
		void
	);
	
	/// \brief Accessor method to check for parsing errors
	/// \details The parsing methods typically execute in a separate thread
	/// and is therefore unable to provide return codes directly. This method
	/// provides access to the shared memory where the return code is stored.
	/// \return SUCCESS
	/// \return SERIAL_TRANSFER_FAILURE
	/// \see sensors::parseQueriedData
	/// \see sensors::parseStreamingData
	ReturnCode
	getParseError (
		void
	);
	
	/// \brief Function to receive serial data
	/// \details Parses data received from Roomba and stores
	/// it in memory accessible by the OICommand object.
	void
	parseSerialData (
		void
	);
	
	/// \brief Stores the baud code
	/// \details The baud code is used when calculating the
	/// time required to execute a sensor query transaction.
	/// \return SUCCESS
	/// \return INVALID_PARAMETER
	/// \see OICommand::sensors
	/// \see OICommand::queryList
	ReturnCode
	setBaudCode (
		const BaudCode baud_code_
	);
	
	/// \brief Function to store parse key
	/// \details A parsing key is generated during the call
	/// to queryList() or sensors() to describe the format
	/// of the data returned by the iRobot® Roomba.
	/// \param [in] parse_key_ An array of bytes describing
	/// the data requested from the iRobot® Roomba.
	/// \n Index 0 contains the length of the array.
	/// \n The remaining values are the packet ids of the
	/// data requested from the iRobot® Roomba.
	/// \return SUCCESS
	/// \return INVALID_PARAMETER
	/// \see OICommand::sensors
	/// \see OICommand::queryList
	ReturnCode
	setParseKey (
		PacketId const * const parse_key_
	);
	
	/// \brief Provides access to sensor data
	/// \param [in] packet_id_ The packet id of the sensor
	/// who's value you want
	/// \param [out] value_ A pointer to the sixteen-bit
	/// field to store the value of the requested sensor
	/// \param [out] is_signed_ A boolean indicating if the
	/// value of the requested sensor is signed or unsigned
	/// \return SUCCESS
	/// \return INVALID_PARAMETER
	/// \return SERIAL_TRANSFER_FAILURE
	ReturnCode
	valueOfSensor (
		const PacketId packet_id_,
		uint_opt16_t * const value_,
		bool * const is_signed_
	);
} // namespace sensor
} // namespace oi
} // namespace series500
} // namespace roomba

#endif

/* Created and copyrighted by Zachary J. Fields. All rights reserved. */
