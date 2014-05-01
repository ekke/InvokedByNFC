/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2

TabbedPane {
    id: rootPane
    
    Tab {
        id: nfcTab
        Page {
            Container {
                Label {
                    text: "The NFC Tab"
                }
            }
        }
    }
    Tab {
        id: doSomeWorkTab
        Page {
            Container {
                Label {
                    text: "Hello: Invoked by NFC Tag with ID: "
                }
                Label {
                    id: nfcID
                    text: "??"
                }
            }
        }
    }
    function onTouchedId(tagId){
        nfcID.text = tagId
        if(activeTab != doSomeWorkTab){
            activeTab = doSomeWorkTab
        }
    }
    onCreationCompleted: {
        appNFC.touchedId.connect(onTouchedId)
    }
}
