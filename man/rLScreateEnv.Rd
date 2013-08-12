\name{rLScreateEnv}
\alias{rLScreateEnv}

\title{Create a new instance of LINDO API environment object.}

\description{
 R interface function for LINDO API function \code{LScreateEnv}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 There is no argument for this function. It goes to folder "LINDOAPI_HOME/license" to 
 locate the license key file and create the LINDO API environment object. 
}

\usage{
rLScreateEnv()
}

\value{
 If successful, rLScreateEnv returns a LINDO API evriorment object; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSdeleteEnv}}
}
