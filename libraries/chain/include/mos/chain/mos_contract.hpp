#pragma once

#include <mos/chain/types.hpp>
#include <mos/chain/contract_types.hpp>

namespace mos { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_mos_newaccount(apply_context&);
   void apply_mos_updateauth(apply_context&);
   void apply_mos_deleteauth(apply_context&);
   void apply_mos_linkauth(apply_context&);
   void apply_mos_unlinkauth(apply_context&);

   /*
   void apply_mos_postrecovery(apply_context&);
   void apply_mos_passrecovery(apply_context&);
   void apply_mos_vetorecovery(apply_context&);
   */

   void apply_mos_setcode(apply_context&);
   void apply_mos_setabi(apply_context&);

   void apply_mos_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace mos::chain
