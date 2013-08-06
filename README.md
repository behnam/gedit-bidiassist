gedit-bidiassist
================

__BidiAssist__ (short for _Bidirectional Assistant_) is a Gedit plugin helping users with their bidirectional (plain) texts


Features
--------

Here are current features:
* __Paragraph Direction__
  * _Left to Right_ Sets the direction of selected paragraphs explicitly to left-to-right
  * _Right to Left_ Sets the direction of selected paragraphs explicitly to right-to-left
  * _Clear_ Removes the explicit direction of selected paragraphs

* __Embed Text__
  * _Left to Right_ Marks selected text as embedded left-to-right
  * _Right to Left_ Marks selected text as embedded right-to-left

* __Override Text__
  * _Left to Right_ Enforces the direction of selected text to left-to-right
  * _Right to Left_ Enforces the direction of selected text to right-to-left

* __Clear Bidirectional Characters__ Removes any bidirectional character from the selected text


How to Install
--------------

You should copy the plugin files (from appropriate bziped tarball) to
`~/.gnome2/gedit/plugins/` or `/usr/lib/gedit-2/plugins/`.

The latest version is v0.93 and should work with Gedit <= 2.10:
* GTK-2.0: http://zwnj.org/proj/gedit/bidiassist/bidiassist-0.93.plugin.gtk-2.0.tar.bz2
* GTK-2.6: http://zwnj.org/proj/gedit/bidiassist/bidiassist-0.93.plugin.gtk-2.6.tar.bz2


See Also
--------

* Source Code: https://github.com/behnam/gedit-bidiassist

* GNOME
  * Bug 353805 – GTK+ – Support for keyboard layouts: https://bugzilla.gnome.org/show_bug.cgi?id=353805
  * Bug 353812 – GTK+ – API for Changing Paragraph Direction: https://bugzilla.gnome.org/show_bug.cgi?id=353812
  * Bug 353814 – GTK+ – Adding Bidi features to Context menu: https://bugzilla.gnome.org/show_bug.cgi?id=353814
  * Bug 312006 – Gedit – Adding Bidi features: https://bugzilla.gnome.org/show_bug.cgi?id=312006

* FreeDesktop
  * Specification: bidi-spec: http://freedesktop.org/wiki/Standards/bidi-spec
  * Mailing List: bidi at lists.freedesktop.org: http://freedesktop.org/mailman/listinfo/bidi/

