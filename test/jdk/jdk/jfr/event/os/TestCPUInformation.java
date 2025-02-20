/*
 * Copyright (c) 2013, 2020, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

/*
 * This file has been modified by Loongson Technology in 2021, These
 * modifications are Copyright (c) 2021, Loongson Technology, and are made
 * available on the same license terms set forth above.
 */

package jdk.jfr.event.os;

import java.util.List;

import jdk.jfr.Recording;
import jdk.jfr.consumer.RecordedEvent;
import jdk.test.lib.jfr.EventNames;
import jdk.test.lib.jfr.Events;

/**
 * @test
 * @key jfr
 * @requires vm.hasJFR
 * @library /test/lib
 * @run main/othervm jdk.jfr.event.os.TestCPUInformation
 */
public class TestCPUInformation {
    private final static String EVENT_NAME = EventNames.CPUInformation;

    public static void main(String[] args) throws Throwable {
        Recording recording = new Recording();
        recording.enable(EVENT_NAME);
        recording.start();
        recording.stop();
        List<RecordedEvent> events = Events.fromRecording(recording);
        Events.hasEvents(events);
        for (RecordedEvent event : events) {
            System.out.println("Event: " + event);
            Events.assertField(event, "hwThreads").atLeast(1);
            Events.assertField(event, "cores").atLeast(1);
            Events.assertField(event, "sockets").atLeast(1);
            Events.assertField(event, "cpu").containsAny("Intel", "AMD", "Unknown x86", "ARM", "PPC", "PowerPC", "AArch64", "s390", "MIPS", "LoongArch");
            Events.assertField(event, "description").containsAny("Intel", "AMD", "Unknown x86", "ARM", "PPC", "PowerPC", "AArch64", "s390", "MIPS", "LoongArch");
        }
    }
}
