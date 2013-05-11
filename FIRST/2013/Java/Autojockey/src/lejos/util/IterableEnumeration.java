package lejos.util;

import java.util.Enumeration;
import java.util.Iterator;

public class IterableEnumeration implements Iterable {
	  private final Enumeration en;
	  public IterableEnumeration(Enumeration en) {
	    this.en = en;
	  }
	  // return an adaptor for the Enumeration
	  public Iterator iterator() {
	    return new Iterator() {
	      public boolean hasNext() {
	        return en.hasMoreElements();
	      }
	      public Object next() {
	        return en.nextElement();
	      }
	      public void remove() {
	        throw new UnsupportedOperationException();
	      }
	    };
	  }
	}

