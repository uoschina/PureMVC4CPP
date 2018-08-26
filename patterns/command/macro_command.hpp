#ifndef __MACRO_COMMAND_HPP__
#define __MACRO_COMMAND_HPP__
#include <string>
#include <vector>

class MacroCommand :public Notifier ,public ICommand
{

    public:
        typedef std::vector<ICommand*> SubCommands; 
		typedef SubCommands::iterator SubCommandsItr; 

        /**
         * Constructor. 
         * 
         * <P>
         * You should not need to define a constructor, 
         * instead, override the <code>initializeMacroCommand</code>
         * method.</P>
         * 
         * <P>
         * If your subclass does define a constructor, be 
         * sure to call <code>super()</code>.</P>
         */
        MacroCommand()
        {
            initializeMacroCommand();			
        }

        /**
         * Initialize the <code>MacroCommand</code>.
         * 
         * <P>
         * In your subclass, override this method to 
         * initialize the <code>MacroCommand</code>'s <i>SubCommand</i>  
         * list with <code>ICommand</code> class references like 
         * this:</P>
         * 
         * <listing>
         *		// Initialize MyMacroCommand
         *		override protected function initializeMacroCommand( ) : void
         *		{
         *			addSubCommand( com.me.myapp.controller.FirstCommand );
         *			addSubCommand( com.me.myapp.controller.SecondCommand );
         *			addSubCommand( com.me.myapp.controller.ThirdCommand );
         *		}
         * </listing>
         * 
         * <P>
         * Note that <i>SubCommand</i>s may be any <code>ICommand</code> implementor,
         * <code>MacroCommand</code>s or <code>SimpleCommands</code> are both acceptable.
         */
        void initializeMacroCommand()
        {
        }

        /**
         * Add a <i>SubCommand</i>.
         * 
         * <P>
         * The <i>SubCommands</i> will be called in First In/First Out (FIFO)
         * order.</P>
         * 
         * @param commandClassRef a reference to the <code>Class</code> of the <code>ICommand</code>.
         */
        void addSubCommand( ICommand *pCmd )
        {
            m_subCommands.push_back(pCmd);
        }

        /** 
         * Execute this <code>MacroCommand</code>'s <i>SubCommands</i>.
         * 
         * <P>
         * The <i>SubCommands</i> will be called in First In/First Out (FIFO)
         * order. 
         * 
         * @param notification the <code>INotification</code> object to be passsed to each <i>SubCommand</i>.
         */
        void execute( notification:INotification ) 
        {
            for (SubCommands::iterator itr = m_subCommands.begin(); itr != m_subCommands.end(); ++itr)
            {
				ICommand * pCmd = *itr;
				pCmd->execute(notification);

                //var commandClassRef : Class = m_subCommands.shift();
                //var commandInstance : ICommand = new commandClassRef();
                //commandInstance.execute( notification );
                
            }
        }
    private:
        SubCommands m_subCommands;
};

#endif // 

