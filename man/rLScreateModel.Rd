\name{rLScreateModel}
\alias{rLScreateModel}

\title{Create a new instance of LINDO API model object.}

\description{
 R interface function for LINDO API function \code{LScreateModel}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 Before this function is called, \code{\link{rLScreateEnv}} must be called to get a valid
 LINDO API environment object.
}

\usage{
rLScreateModel(env)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
}

\value{
 If successful, rLScreateModel returns a LINDO API model object; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSdeleteModel}}
}
