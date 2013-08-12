\name{rLSsampCreate}
\alias{rLSsampCreate}

\title{Create an instance of a sample of specified distribution.}

\description{
 R interface function for LINDO API function \code{LSsampCreate}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 Before this function is called, \code{\link{rLScreateEnv}} must be called to get a valid
 LINDO API environment object.
}

\usage{
rLSsampCreate(env,nDistType)
}

\arguments{
 \item{env}{A LINDO API environment object, returned by \code{\link{rLScreateEnv}}.}
 \item{nDistType}{The distribution type.}
}

\value{
 If successful, rLSsampCreate returns a LINDO API sample object; 
 Otherwise, it returns NULL.
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
