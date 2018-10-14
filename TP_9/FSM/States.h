#pragma once
#include<iostream>
#include<boost/statechart/state_machine.hpp>
#include<boost/statechart/simple_state.hpp>
#include<boost/statechart/event.hpp>
#include<boost/statechart/transition.hpp>
#include<boost/statechart/custom_reaction.hpp>
#include <boost/context/execution_context.hpp>
#include "Events.h"

namespace SC = boost::statechart; //short name


class TwitterFSM;//foward declarations
class InitState;
class ParsingCMD;
class WaitingForTweets;
class ParsingJSON;
class DisplayingTweets;
class End;




class InitState : public SC::simple_state<InitState, TwitterFSM>
{
	typedef SC::transition<StartEvent, ParsingCMD> react;
	
};



class WaitingForTweets : public SC::simple_state<WaitingForTweets, TwitterFSM>
{

};

class DisplayingTweets : public SC::simple_state<DisplayingTweets, TwitterFSM>
{

};

class End : public SC::simple_state<End, TwitterFSM>
{

};


