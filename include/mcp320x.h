#ifndef MCP320X_H_
#define MCP320X_H_
/**\cond INTERNAL*/
#include <adc.h>
#define ADC_PRV
#include <adc_prv.h>
#include <spi.h>
#include <FreeRTOS.h>
#include <task.h>
extern const struct adc_ops mcp320x_ops;
struct adc_mcp320x_contoller {
	struct hal gen;
	struct adc_mcp320x *channels[8];
	struct spi_slave *slave;
	
};
struct adc_mcp320x {
	struct adc_generic gen;
	struct adc_mcp320x_contoller *adcc;
	uint32_t bits;
	uint32_t ticks;
	uint32_t channelID;
	bool running;
	OS_DEFINE_TASK(task, 500);
	bool (*callback)(struct adc *adc, uint32_t channel, int32_t value, void *data);
	void *data;
};

#define ADD_MCP320X_CHANNEL(ID, _channelID) \
	struct adc_mcp320x mcp320x_##ID##_##_channelID = { \
		ADC_INIT_DEV(mcp320x) \
		HAL_NAME("TI MCP320x " #ID "Channel " #_channelID) \
		.adcc = &mcp320x_##ID, \
		.channelID = _channelID, \
	};\
	ADC_ADDDEV(mcp320x, mcp320x_##ID##_##_channelID)
/**\endcond*/

void *mcp320x_contoller_init(uint32_t index);
int32_t mcp320x_connect(void *ac, struct spi *spi, uint8_t cs, uint16_t gpio);

#define ADD_MCP320X(ID) \
	extern struct adc_mcp320x_contoller mcp320x_##ID;\
	ADD_MCP320X_CHANNEL(ID, 0); \
	ADD_MCP320X_CHANNEL(ID, 1); \
	ADD_MCP320X_CHANNEL(ID, 2); \
	ADD_MCP320X_CHANNEL(ID, 3); \
	ADD_MCP320X_CHANNEL(ID, 4); \
	ADD_MCP320X_CHANNEL(ID, 5); \
	ADD_MCP320X_CHANNEL(ID, 6); \
	ADD_MCP320X_CHANNEL(ID, 7); \
	struct adc_mcp320x_contoller mcp320x_##ID = { \
		HAL_NAME("TI MCP320x " #ID) \
		.channels = { \
			&mcp320x_##ID##_0, \
			&mcp320x_##ID##_1, \
			&mcp320x_##ID##_2, \
			&mcp320x_##ID##_3, \
		}, \
	}; \
	HAL_ADDDEV(hal, mcp320x, mcp320x_##ID)

#define MCP320X_ID(ID) HAL_GET_ID(hal, mcp320x, mcp320x_##ID)
#define MCP320X_ID_CHANNEL(ID, _channelID) HAL_GET_ID(adc, mcp320x, mcp320x_##ID##_##_channelID)
#endif

