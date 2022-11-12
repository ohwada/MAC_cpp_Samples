/*
 * A simple implementation of chameneos benchmark (this implementation is
 * based on definition which was used in The Great Language Shootout Gate
 * in 2007).
 *
 * There are four chameneos with different colors.
 * There is a meeting place for them.
 *
 * Each creature is trying to go to the meeting place. Only two of them
 * could do that at the same time. During the meeting they should change
 * their colors by special rule. Then they should leave the meeting place
 * and do the next attempt to go to the meeting place again.
 *
 * There is a limitation for meeting count. When this limit is reached
 * every creature should receive a special color FADED and report count of
 * other creatures met.
 *
 * Total count of meetings should be reported at the end of the test.
 *
 * This sample is implemented here with two different types of agents:
 * - the first one is the type of meeting place. Agent of that type does
 *   several task. It handles meetings of creatures and count meetings.
 *   When the limit of meeting is reached that agent inform all creatures
 *   about test shutdown. Then the agent receives shutdown acknowledgements
 *   from creatures and calculates total meeting count;
 * - the second one is the type of creature. Agents of that type are trying
 *   to reach meeting place. They send meeting requests to meeting place agent
 *   and handle meeting result or shutdown signal.
 */

#include <iostream>
#include <iterator>
#include <numeric>
#include <cstdlib>

#include <so_5/all.hpp>

enum color_t
	{
		BLUE = 0,
		RED = 1,
		YELLOW = 2,
		FADED = 3
	};

struct msg_meeting_request
	{
		so_5::mbox_t m_who;
		color_t m_color;
	};

struct msg_meeting_result
	{
		color_t m_color;
	};

struct msg_shutdown_request final : public so_5::signal_t {};

struct msg_shutdown_ack
	{
		int m_creatures_met;
	};

class a_meeting_place_t final : public so_5::agent_t
	{
	public :
		a_meeting_place_t(
			context_t ctx,
			int creatures,
			int meetings )
			:	so_5::agent_t( ctx )
			,	m_creatures_alive( creatures )	
			,	m_remaining_meetings( meetings )
			,	m_total_meetings( 0 )
			{}

		void so_define_agent() override
			{
				this >>= st_empty;

				st_empty
					.event( &a_meeting_place_t::evt_first_creature )
					.event( &a_meeting_place_t::evt_shutdown_ack );

				st_one_creature_inside
					.event( &a_meeting_place_t::evt_second_creature );
			}

	private :
		void evt_first_creature(
			const msg_meeting_request & evt )
			{
				if( m_remaining_meetings )
				{
					this >>= st_one_creature_inside;

					m_first_creature_mbox = evt.m_who;
					m_first_creature_color = evt.m_color;
				}
				else
					so_5::send< msg_shutdown_request >( evt.m_who );
			}

		void evt_second_creature(
			const msg_meeting_request & evt )
			{
				so_5::send< msg_meeting_result >(
						evt.m_who, m_first_creature_color );
				so_5::send< msg_meeting_result >(
						m_first_creature_mbox, evt.m_color );

				--m_remaining_meetings;

				this >>= st_empty;
			}

		void evt_shutdown_ack(
			const msg_shutdown_ack & evt )
			{
				m_total_meetings += evt.m_creatures_met;
				
				if( 0 >= --m_creatures_alive )
				{
					std::cout << "Total: " << m_total_meetings << std::endl;

					so_environment().stop();
				}
			}

		const state_t st_empty{ this, "empty" };
		const state_t st_one_creature_inside{ this, "one_creature_inside" };

		int m_creatures_alive;
		int m_remaining_meetings;
		int m_total_meetings;

		so_5::mbox_t m_first_creature_mbox;
		color_t m_first_creature_color = { FADED };
	};

class a_creature_t final : public so_5::agent_t
	{
	public :
		a_creature_t(
			context_t ctx,
			so_5::mbox_t meeting_place_mbox,
			color_t color )
			:	so_5::agent_t( ctx )
			,	m_meeting_place_mbox( std::move(meeting_place_mbox) )
			,	m_meeting_counter( 0 )
			,	m_color( color )
			{}

		void so_define_agent() override
			{
				so_default_state()
					.event( &a_creature_t::evt_meeting_result )
					.event( &a_creature_t::evt_shutdown_request );
			}

		void so_evt_start() override
			{
				so_5::send< msg_meeting_request >(
						m_meeting_place_mbox,
						so_direct_mbox(), m_color );
			}

	private :
		void evt_meeting_result(
			const msg_meeting_result & evt )
			{
				m_color = complement( evt.m_color );
				m_meeting_counter++;

				so_5::send< msg_meeting_request >(
						m_meeting_place_mbox,
						so_direct_mbox(), m_color );
			}

		void evt_shutdown_request( mhood_t< msg_shutdown_request > )
			{
				m_color = FADED;
				std::cout << "Creatures met: " << m_meeting_counter << std::endl;

				so_5::send< msg_shutdown_ack >(
						m_meeting_place_mbox, m_meeting_counter );
			}

		const so_5::mbox_t m_meeting_place_mbox;

		int m_meeting_counter;

		color_t m_color;

		color_t complement( color_t other ) const noexcept
			{
				switch( m_color )
					{
					case BLUE:
						return other == RED ? YELLOW : RED;
					case RED:
						return other == BLUE ? YELLOW : BLUE;
					case YELLOW:
						return other == BLUE ? RED : BLUE;
					case FADED:
						break;
					}
				return m_color;
			}
	};

const int creature_count = 4;

void init( so_5::environment_t & env, int meetings )
	{
		env.introduce_coop(
				so_5::disp::active_obj::make_dispatcher( env ).binder(),
				[meetings]( so_5::coop_t & coop )
				{
					color_t creature_colors[ creature_count ] =
						{ BLUE, RED, YELLOW, BLUE };

					auto a_meeting_place = coop.make_agent< a_meeting_place_t >(
							creature_count,
							meetings );
					
					for( int i = 0; i != creature_count; ++i )
						{
							coop.make_agent< a_creature_t >(
									a_meeting_place->so_direct_mbox(),
									creature_colors[ i ] );
						}
				} );
	}

int main( int argc, char ** argv )
{
	try
	{
		so_5::launch(
				[argc, argv]( so_5::environment_t & env ) {
					const int meetings = 2 == argc ? std::atoi( argv[1] ) : 10;
					init( env, meetings );
				} );
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

