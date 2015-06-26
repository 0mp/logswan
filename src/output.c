/*****************************************************************************/
/*                                                                           */
/* Logswan (c) by Frederic Cambus 2015                                       */
/* https://github.com/fcambus/logswan                                        */
/*                                                                           */
/* Created:      2015/05/31                                                  */
/* Last Updated: 2015/06/24                                                  */
/*                                                                           */
/* Logswan is released under the BSD 3-Clause license.                       */
/* See LICENSE file for details.                                             */
/*                                                                           */
/*****************************************************************************/

#include <GeoIP.h>
#include <jansson.h>

#include "results.h"

void output(Results results) {
	json_t *jsonObject = json_object();
	json_t *hitsObject = json_object();
	json_t *countriesArray = json_array();
	json_t *hoursArray = json_array();
			
	for (int loop=0; loop<255; loop++) {
		if (results.countries[loop] != 0) {
			json_array_append_new(countriesArray, json_pack("{s:s, s:i}", "data", GeoIP_code_by_id(loop), "hits", results.countries[loop]));
		}
	}

	for (int loop=0; loop<24; loop++) {
		if (results.hours[loop] != 0) {
			json_array_append_new(hoursArray, json_pack("{s:i, s:i}", "data", loop, "hits", results.hours[loop]));
		}
	}

	json_object_set_new(hitsObject, "ipv4", json_integer(results.hitsIPv4));
	json_object_set_new(hitsObject, "ipv6", json_integer(results.hitsIPv6));
	json_object_set_new(hitsObject, "total", json_integer(results.hits));
	json_object_set_new(hitsObject, "countries", countriesArray);
	json_object_set_new(hitsObject, "hours", hoursArray);

	json_object_set_new(jsonObject, "date", json_string(results.timeStamp));
	json_object_set_new(jsonObject, "file_size", json_integer(results.fileSize));
	json_object_set_new(jsonObject, "processed_lines", json_integer(results.processedLines));
	json_object_set_new(jsonObject, "invalid_lines", json_integer(results.invalidLines));
	json_object_set_new(jsonObject, "bandwidth", json_integer(results.bandwidth));
	json_object_set_new(jsonObject, "runtime", json_real(results.runtime));
	json_object_set_new(jsonObject, "hits", hitsObject);

	printf("%s", json_dumps(jsonObject, JSON_INDENT(3) | JSON_PRESERVE_ORDER));
}
