\name{rLSdeleteEnv}
\alias{rLSdeleteEnv}

\title{Delete LINDO API environment object.}

\description{
 R interface function for LINDO API function \code{LSdeleteEnv}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 The memory used by the environment object is freed. 
}

\usage{
rLSdeleteEnv(env)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLScreateEnv}}
}
