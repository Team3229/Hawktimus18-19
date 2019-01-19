/*
 * Debug.h
 *
 *  Created on: May 3, 2018
 *      Author: luke
 */

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

//#define USEDEBUG //Uncomment or comment to use or not use

#ifdef USEDEBUG
#define debug(x) std::cout << x
#else
#define debug(x)
#endif

#endif /* SRC_DEBUG_H_ */
